package com.marketdataclient;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Map;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import com.marketdataclient.ICICIResultParser.exchangeInfo;
import com.marketdataclient.ICICIWorker.tickDestination;
import com.marketdataclient.kdbfeedhandler.ICICIKdbTickPublisher;

import kx.c.KException;

public class Main
{
	private enum executionType
	{
		Threaded, Serial
	}

	final static Logger logger = LogManager.getLogger(Main.class);

	public static void main(String[] args)
	{

		// Kick Start the application.
		logger.info("Starting the MarketDataClient Application.");

		// First load the stock symbol names from a Separate Configuration file.
		String[] stockItems = loadEquitySymbolsFromConfigFile();

		// Load the properties Configuration file for the marketDataConfig.
		MarketDataConfigManager marketDataConfig = new MarketDataConfigManager();

		String executionMode = marketDataConfig.getConfigMap().get("executionMode");

		if (executionMode.equals(executionType.Threaded.toString()))
			runInThreadedMode(stockItems, marketDataConfig);
		else
			runInSerialMode(stockItems, marketDataConfig);

		System.exit(0);
	}

	static private void runInThreadedMode(String[] stockItems, MarketDataConfigManager marketDataConfig)
	{

		Boolean tickDisplayMode = Boolean.getBoolean(marketDataConfig.getConfigMap().get("displayMode"));
		ExecutorService executor = Executors.newFixedThreadPool(stockItems.length);

		ICICIWorker.setPrintTickResults(tickDisplayMode);
		Boolean NSEStatus = Boolean.parseBoolean(marketDataConfig.getConfigMap().get("NSEStatus"));
		Boolean BSEStatus = Boolean.parseBoolean(marketDataConfig.getConfigMap().get("BSEStatus"));
		ICICIWorker.setNSE(NSEStatus);
		ICICIWorker.setBSE(BSEStatus);
		ICICIWorker.setDestination(tickDestination.valueOf(marketDataConfig.getConfigMap().get("resultWriterDestination")));
		
		Long tickSequenceLimit = Long.parseLong(marketDataConfig.getConfigMap().get("maxTickLimit"));
		ICICIWorker.setTickSequenceLimit(tickSequenceLimit);

		int cycleSleepDuration = Integer.parseInt(marketDataConfig.getConfigMap().get("cycleSleepDurationMilliSecs"));
		ICICIWorker.setCycleSleepDuration(cycleSleepDuration);

		// Now create a arrayBlockingQueue of size number of stock items
		// multiplied by maxTickLimit to make sure we have enough size to cover
		// at all times. More aggressive strategy may be to allocate only around
		// half of the size of above to save on memory.

		float capacityAdjFactor = Float.parseFloat(marketDataConfig.getConfigMap().get("queueCapacityAdjFactor"));
		int queueSize = (int) ((tickSequenceLimit.intValue() * stockItems.length) * capacityAdjFactor);
		TickDataQueue.setTickDataQueue(new ArrayBlockingQueue<String>(queueSize));

		logger.info("Set the below configuration for the worker threaded. The tick display mode is set to " + tickDisplayMode.toString() + ".NSE Publishing is set to " + NSEStatus
				+ ".BSE Publishing status is set to " + BSEStatus + ".");

		if (!tickDisplayMode)
			ICICIHelperUtils.printCsvHeader();

		for (int i = 0; i < stockItems.length; i++)
		{
			Runnable worker = new ICICIWorker(stockItems[i]);
			executor.execute(worker);
		}

		// Start the KDB processing thread via below.
		int kdbPublisherThreads = Integer.parseInt(marketDataConfig.getConfigMap().get("KdbPublishThreads"));
		String kdbServer = marketDataConfig.getConfigMap().get("kdbServer");
		int kdbPort = Integer.parseInt(marketDataConfig.getConfigMap().get("kdbPort"));

		ICICIKdbTickPublisher kdbTickPublisher = new ICICIKdbTickPublisher(kdbPublisherThreads, kdbServer, kdbPort);
		kdbTickPublisher.start();

		while (!ICICIWorker.allThreadsFinished())
		{
			try
			{
				Thread.sleep(1000);
				logger.info("There are " + TickDataQueue.getTickDataQueue().size() + " Items in the queue waiting to be processed");
			} catch (InterruptedException e)
			{

			}
		}

		logger.info("All stock publisher threads have finished.");

		while (TickDataQueue.getTickDataQueue().size() > 0)
		{
			logger.info("There are still " + TickDataQueue.getTickDataQueue().size() + " Items in the queue waiting to be processed");
			try
			{
				Thread.sleep(1000);
			} catch (InterruptedException e)
			{

			}
		}

		// Signal to stop the KDB publishing threads now.
		ICICIKdbTickPublisher.setKeepPublishing(false);
		executor.shutdownNow();
		kdbTickPublisher.getExecutor().shutdownNow();

	}

	static private void runInSerialMode(String[] stockItems, MarketDataConfigManager marketDataConfig)
	{
		boolean tickDisplayMode = Boolean.getBoolean(marketDataConfig.getConfigMap().get("displayMode"));
		int tickCount = 1;
		while (tickCount < 1000)
		{
			for (int i = 0; i < stockItems.length; ++i)
			{
				String stockName = stockItems[i];
				ICICIPrices priceItem = new ICICIPrices(stockName);
				Map<String, Object> streamResultMap = priceItem.streamPrices();
				if (!streamResultMap.isEmpty())
				{
					ICICIResultParser nseResultParser = new ICICIResultParser(streamResultMap, exchangeInfo.NSE);
					if (tickDisplayMode)
						ICICIHelperUtils.printResults(streamResultMap, stockName, tickCount);
					else
						ICICIHelperUtils.csvFormatResultPrinter(nseResultParser, stockName, tickCount);
				}
			}
			logger.info("sequence count at " + tickCount);
			++tickCount;
		}
	}

	private void runYahooDemo()
	{
		YahooPrices samplePriceItem = new YahooPrices("SGDINR=X", "nl1abb6a5");
		int prevHashCode = 0, hashCode = 0;
		int count = 1;
		while (count <= 0)
		{
			String[] result = samplePriceItem.getYahooPrices();
			hashCode = samplePriceItem.getHashCode();
			if (hashCode != prevHashCode)
			{
				System.out.println(result[0] + "|" + result[1] + "|" + result[2] + "|" + result[3] + "|" + result[4] + "|" + result[5]);
				System.out.println("HashCode is = " + hashCode);
				prevHashCode = hashCode;
			}
			--count;
		}
	}

	private static String[] loadEquitySymbolsFromConfigFile()
	{

		BufferedReader b = null;
		ArrayList<String> stockSymbols = new ArrayList<String>();
		String filePath = System.getProperty("user.dir") + "/resources/eqsymbols.cfg";
		File f = new File(filePath);
		try
		{
			b = new BufferedReader(new FileReader(f));
			logger.info("Successfully Loaded the config file at path = " + filePath);

		} catch (FileNotFoundException e)
		{
			logger.error("Failed to get the config file. please verify the path = " + filePath);
			logger.error("Exiting the Application");
			System.exit(1);
		}
		String readLine = "";
		try
		{
			while ((readLine = b.readLine()) != null)
			{
				if (!readLine.trim().isEmpty())
					stockSymbols.add(readLine);
			}
		} catch (IOException e)
		{
			logger.warn("Error while reading the equity symbols config file. returning empty array");
		}

		try
		{
			b.close();
		} catch (IOException e)
		{
			logger.error("Error closing the file stream for the equity symbols config file. Please verify");
			logger.warn("The stack trace is as follows " + e.getStackTrace().toString());
		}

		if (stockSymbols.size() == 0)
		{
			logger.error("Can not load or find any stock symbols from config file. Exiting the application with failure status");
			System.exit(1);
		} else
			logger.info("Successfully loaded " + stockSymbols.size() + " symbols from the config file.");

		String[] stocksArray = new String[stockSymbols.size()];
		stocksArray = stockSymbols.toArray(stocksArray);
		return (stocksArray);
	}
}
