package com.marketdataclient;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import com.marketdataclient.icici.ICICIWorkerManager;
import com.marketdataclient.configmanager.MarketDataConfigManager;

public class Main
{
	final static Logger logger = LogManager.getLogger(Main.class);

	public static void main(String[] args)
	{
		// Set a default publisher Type.
		String publihserType = "ICICI";
		
		// Kick Start the application with initial log message.
		logger.info("Starting the MarketDataClient Application.");

		// Testing some CNBC HTTP post method for the cnbc real time quote website.
//		CNBCHttpPostExample httpExample = new CNBCHttpPostExample();
//		httpExample.httpPost("INR=");
//		System.exit(1);
		
		// Load the properties Configuration file for the marketDataConfig.
		MarketDataConfigManager marketDataConfig = new MarketDataConfigManager(publihserType);

		// Load the stock symbols required for the WorkerManager.
		String[] symbolList = marketDataConfig.loadEquitySymbolsFromConfigFile();

		// Kick start the ICICI Worker Manager instance.
		ICICIWorkerManager iciciWorkerManager = new ICICIWorkerManager(marketDataConfig, symbolList);
		iciciWorkerManager.start();
		System.exit(0);
	}
}
