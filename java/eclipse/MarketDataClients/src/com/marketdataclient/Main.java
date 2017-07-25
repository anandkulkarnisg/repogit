package com.marketdataclient;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import com.marketdataclient.icici.ICICIWorkerManager;
import com.marketdataclient.cnbc.CNBCWorkerManager;
import com.marketdataclient.configmanager.MarketDataConfigManager;

public class Main
{
	final static Logger logger = LogManager.getLogger(Main.class);

	public static void main(String[] args)
	{
		// Set a default publisher Type.
		String publisherType = "icici";
		if (args.length > 0)
			publisherType = args[0];

		// Kick Start the application with initial log message.
		logger.info("Starting the MarketDataClient Application.");

		// Load the properties Configuration file for the marketDataConfig.
		MarketDataConfigManager marketDataConfig = new MarketDataConfigManager(publisherType);

		// Load the stock symbols required for the WorkerManager.
		String[] symbolList = marketDataConfig.loadEquitySymbolsFromConfigFile();

		// Invoke the CNBC Worker Manager now.
		if (publisherType.equalsIgnoreCase("cnbc"))
		{
			CNBCWorkerManager cnbcWorkerManager = new CNBCWorkerManager(marketDataConfig, symbolList);
			cnbcWorkerManager.start();
			System.exit(0);
		}

		// Kick start the ICICI Worker Manager instance.
		if (publisherType.equalsIgnoreCase("icici"))
		{
			ICICIWorkerManager iciciWorkerManager = new ICICIWorkerManager(marketDataConfig, symbolList);
			iciciWorkerManager.start();
			System.exit(0);
		}
		System.exit(0);
	}
}
