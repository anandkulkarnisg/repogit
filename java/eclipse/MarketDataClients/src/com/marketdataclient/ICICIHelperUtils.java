package com.marketdataclient;

import java.util.Map;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.joda.time.LocalDate;

public class ICICIHelperUtils
{

	final static Logger logger = LogManager.getLogger(ICICIHelperUtils.class);

	static void printResults(Map<String, Object> streamResultMap, String stockName, int counter)
	{
		System.out.println("---------------------------- " + stockName + ", tick sequence = " + counter + "START ---------------------------------");
		for (Map.Entry<String, Object> entry : streamResultMap.entrySet())
			System.out.println("key=" + entry.getKey() + " --->  value=" + entry.getValue().toString());
		System.out.println("----------------------------" + stockName + ", tick sequence = " + counter + " END ---------------------------------");
		System.out.println("Finished tick count sequence =" + counter);
	}

	static void csvFormatResultPrinter(ICICIResultParser resultParser, String stockName, int counter)
	{

		String csvResult = null;

		try
		{
			// Get the exchange info.
			String exchangeName = resultParser.getExchange().toString();

			// Test all double Prices.
			double highPrice = resultParser.getHighPriceRange();
			double lifeTimeHighPrice = resultParser.getLifeTimeHigh();
			double lifeTimeLowPrice = resultParser.getLifeTimeLow();
			double dayHighPrice = resultParser.getDayHigh();
			double lastTradedPrice = resultParser.getLastTradePrice();
			double week52HighPrice = resultParser.get52WeekHighPrice();
			double week52LowPrice = resultParser.get52WeekLowPrice();
			double bestBidPrice = resultParser.getBestBidPrice();
			double bestAskPrice = resultParser.getBestOfferPrice();
			double dayOpenPrice = resultParser.getDayOpenPrice();
			double dayClosePrice = resultParser.getDayClosePrice();
			double prevDayClosePrice = resultParser.getPreviousDayClosePrice();
			double dayLowPrice = resultParser.getDayLowPrice();
			double highPriceRange = resultParser.getHighPriceRangePrice();
			double lowPriceRange = resultParser.getLowPriceRangePrice();
			double absolutePriceChange = resultParser.getAbsoluteChangePrice();
			double percentPriceChange = resultParser.getPercentChange();

			// Test all the long prices.
			long bestBidQuantity = resultParser.getBestBidQuantity();
			long bestAskQuantity = resultParser.getBestOfferQuantity();
			long dayVolume = resultParser.getDayVolume();

			// Test all the Date items.
			LocalDate valueDate = resultParser.getValueDate();

			// Lastly the Time as a string.
			String lastTradedTime = resultParser.getLastTradedTime();

			// The resulting CSV string is built below.
			csvResult = counter + "," + exchangeName + "," + stockName + "," + highPrice + "," + lifeTimeHighPrice + "," + lifeTimeLowPrice + "," + dayHighPrice + ","
					+ lastTradedPrice + "," + week52HighPrice + "," + week52LowPrice + "," + bestBidPrice + "," + bestAskPrice + "," + dayOpenPrice + "," + dayClosePrice + ","
					+ prevDayClosePrice + "," + +dayLowPrice + "," + highPriceRange + "," + lowPriceRange + "," + absolutePriceChange + "," + percentPriceChange + ","
					+ bestBidQuantity + "," + bestAskQuantity + "," + dayVolume + "," + valueDate + "," + lastTradedTime;

		} catch (Exception e)
		{
			logger.error(
					"Caught exception while parsing and processing data for symbol = " + stockName + ", The tick sequence was at " + counter + "The exception details are below");
			logger.error(e.getStackTrace().toString());
		}

		logger.info("Successfully parsed and published the data for symbol = " + stockName + ", The tick sequence was at " + counter + ".");
		// logger.info(csvResult);
		// System.out.println(csvResult);

	}

	static void printCsvHeader()
	{
		// System.out.println(
		// "tickSequence,exchangeName,stockName,highPrice,lifeTimeHighPrice,lifeTimeLowPrice,dayHighPrice,lastTradedPrice,week52HighPrice,week52LowPrice,bestBidPrice,bestAskPrice,dayOpenPrice,dayClosePrice,prevDayClosePrice,dayLowPrice,highPriceRange,lowPriceRange,absolutePriceChange,percentPriceChange,bestBidQuantity,bestAskQuantity,dayVolume,date,lastTradedTime");
		logger.info(
				"tickSequence,exchangeName,stockName,highPrice,lifeTimeHighPrice,lifeTimeLowPrice,dayHighPrice,lastTradedPrice,week52HighPrice,week52LowPrice,bestBidPrice,bestAskPrice,dayOpenPrice,dayClosePrice,prevDayClosePrice,dayLowPrice,highPriceRange,lowPriceRange,absolutePriceChange,percentPriceChange,bestBidQuantity,bestAskQuantity,dayVolume,date,lastTradedTime");
	}

}
