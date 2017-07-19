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
import com.marketdataclient.ICICIResultParser.exchangeInfo;

public class Main
{
	public static void main(String[] args)
	{
		String[] stockItems = loadEquitySymbolsFromConfigFile();
		String executionMode = args[0];
		boolean tickDisplayMode = false;

		if (args[1] != null && args[1].equalsIgnoreCase("y"))
			tickDisplayMode = true;

		if (executionMode.equalsIgnoreCase("threaded"))
			runInThreadedMode(stockItems, tickDisplayMode);
		else
			runInSerialMode(stockItems, tickDisplayMode);

		System.exit(0);
	}

	static private void runInThreadedMode(String[] stockItems, boolean tickDisplayMode)
	{

		ExecutorService executor = Executors.newFixedThreadPool(stockItems.length);
		ICICIWorkerThread.setPrintTickResults(tickDisplayMode);
		if(!tickDisplayMode)
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

	static private void runInSerialMode(String[] stockItems, boolean tickDisplayMode)
	{
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

		// String[] stockItems = { "INFTEC", "SININD", "WIPRO", "HCLINF",
		// "HDIL", "GVKPOW", "TCS", "DLFLIM", "GOLDEX", "SUBSYS" };
		BufferedReader b = null;
		ArrayList<String> stockSymbols = new ArrayList<String>();
		String filePath = System.getProperty("user.dir") + "/config/eqsymbols.cfg";
		File f = new File(filePath);
		try
		{
			b = new BufferedReader(new FileReader(f));
		} catch (FileNotFoundException e)
		{
			System.out.println("Failed to get the config file. please verify the below path");
			System.out.println(filePath);
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
			System.out.println("Error loading the config file. returning empty array");
		}

		try
		{
			b.close();
		} catch (IOException e)
		{
			e.printStackTrace();
		}
		String[] stocksArray = new String[stockSymbols.size()];
		stocksArray = stockSymbols.toArray(stocksArray);
		return (stocksArray);
	}
}
