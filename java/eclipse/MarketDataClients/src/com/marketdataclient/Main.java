package com.marketdataclient;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import com.marketdataclient.icici.ICICIWorkerManager;
import com.marketdataclient.cnbc.CNBCHttpPostExample;
import com.marketdataclient.configmanager.MarketDataConfigManager;

public class Main
{
	public enum executionType
	{
		Threaded, Serial
	}

	final static Logger logger = LogManager.getLogger(Main.class);

	public static void main(String[] args)
	{

		// Kick Start the application with initial log message.
		logger.info("Starting the MarketDataClient Application.");

		// Testing some CNBC HTTP post method for the cnbc real time quote
		// website.
		CNBCHttpPostExample httpExample = new CNBCHttpPostExample();
		httpExample.httpPost("@GC.1");
		System.exit(1);

		// First load the stock symbol names from a Separate Configuration file.
		String[] stockItems = loadEquitySymbolsFromConfigFile();

		// Load the properties Configuration file for the marketDataConfig.
		MarketDataConfigManager marketDataConfig = new MarketDataConfigManager();

		// Kick start the ICICI Worker Manager instance.
		ICICIWorkerManager iciciWorkerManager = new ICICIWorkerManager(marketDataConfig, stockItems);
		iciciWorkerManager.start();
		System.exit(0);
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
