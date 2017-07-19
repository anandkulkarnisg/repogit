package com.marketdataclient;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Map;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import com.marketdataclient.ICICIResultParser.exchangeInfo;

public class Main
{

	public enum executionType
	{
		Threaded, Serial
	}

	final static Logger logger = LogManager.getLogger(Main.class);

	public static void main(String[] args)
	{

		logger.info("Starting the MarketDataClient Application.");

		// First load the stock symbol names from a Seperate Config file.
		String[] stockItems = loadEquitySymbolsFromConfigFile();

		// Load the properties config file for the marketDataConfig.
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

		boolean tickDisplayMode = Boolean.getBoolean(marketDataConfig.getConfigMap().get("displayMode"));
		ExecutorService executor = Executors.newFixedThreadPool(stockItems.length);

		ICICIWorkerThread.setPrintTickResults(tickDisplayMode);
		ICICIWorkerThread.setNSE(Boolean.parseBoolean(marketDataConfig.getConfigMap().get("NSEStatus")));
		ICICIWorkerThread.setBSE(Boolean.parseBoolean(marketDataConfig.getConfigMap().get("BSEStatus")));

		if (!tickDisplayMode)
			GenericUtils.printCsvHeader();

		for (int i = 0; i < stockItems.length; i++)
		{
			Runnable worker = new ICICIWorkerThread(stockItems[i]);
			executor.execute(worker);
		}

		while (!ICICIWorkerThread.allThreadsFinished())
		{
			try
			{
				Thread.sleep(1000);
			} catch (InterruptedException e)
			{

			}
		}
		executor.shutdownNow();
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
						GenericUtils.printResults(streamResultMap, stockName, tickCount);
					else
						GenericUtils.csvFormatResultPrinter(nseResultParser, stockName, tickCount);
				}
			}
			System.out.println("sequence count at " + tickCount);
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
		
		if(stockSymbols.size() == 0)
		{
			logger.error("Can not load or find any stock symbols from config file. Exiting the application with failure status");
			System.exit(1);
		}		
		else
			logger.info("Successfully loaded " + stockSymbols.size() + " symbols from the config file.");
		
		String[] stocksArray = new String[stockSymbols.size()];
		stocksArray = stockSymbols.toArray(stocksArray);
		return (stocksArray);
	}
}
