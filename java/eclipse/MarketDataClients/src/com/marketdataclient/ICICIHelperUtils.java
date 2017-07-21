package com.marketdataclient;

import java.sql.Date;
import java.sql.Time;
import java.util.Map;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.joda.time.LocalDate;

import com.marketdataclient.ICICIWorker.tickDestination;

public class ICICIHelperUtils
{

	final static Logger logger = LogManager.getLogger(ICICIHelperUtils.class);

	static void printResults(Map<String, Object> streamResultMap, String stockName, long counter)
	{
		System.out.println("---------------------------- " + stockName + ", tick sequence = " + counter + "START ---------------------------------");
		for (Map.Entry<String, Object> entry : streamResultMap.entrySet())
			System.out.println("key=" + entry.getKey() + " --->  value=" + entry.getValue().toString());
		System.out.println("----------------------------" + stockName + ", tick sequence = " + counter + " END ---------------------------------");
		System.out.println("Finished tick count sequence =" + counter);
	}

	static void csvFormatResultPrinter(ICICIResultParser resultParser, String stockName, long counter)
	{

		String csvResult = null;
		boolean overAllParseStatus = false;

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
			LocalDate dt = resultParser.getValueDate();
			Date valueDate = Date.valueOf(dt.toString());

			Time lastTradedTime;

			// Lastly the Time as we need it. Currently milliseconds from BSE
			// does not work well to java.sql.Time conversion.
			if (resultParser.getExchange().toString().equals("NSE"))
				lastTradedTime = Time.valueOf(resultParser.getLastTradedTime());
			else
			{
				String result = resultParser.getLastTradedTime();
				result = result.substring(0, result.length() - 4);
				lastTradedTime = Time.valueOf(result);
			}

			// The resulting CSV string is built below.
			csvResult = counter + "," + exchangeName + "," + stockName + "," + highPrice + "," + lifeTimeHighPrice + "," + lifeTimeLowPrice + "," + dayHighPrice + ","
					+ lastTradedPrice + "," + week52HighPrice + "," + week52LowPrice + "," + bestBidPrice + "," + bestAskPrice + "," + dayOpenPrice + "," + dayClosePrice + ","
					+ prevDayClosePrice + "," + +dayLowPrice + "," + highPriceRange + "," + lowPriceRange + "," + absolutePriceChange + "," + percentPriceChange + ","
					+ bestBidQuantity + "," + bestAskQuantity + "," + dayVolume + "," + valueDate + "," + lastTradedTime;

			overAllParseStatus = true;

		} catch (Exception e)
		{
			logger.error(
					"Caught exception while parsing and processing data for symbol = " + stockName + ", The tick sequence was at " + counter + "The exception details are below");
			logger.error(e.getStackTrace().toString());
			e.printStackTrace();
		}

		if (overAllParseStatus)
		{

			if (ICICIWorker.getDestination() == tickDestination.STDOUT)
			{
				System.out.println(csvResult);
				logger.info("Successfully parsed and printed to stdout the data for symbol = " + stockName + ", The tick sequence was at " + counter + ".");
			}

			if (ICICIWorker.getDestination() == tickDestination.KDB)
			{

				try
				{
					TickDataQueue.getTickDataQueue().add(csvResult);
					logger.info("Successfully parsed and published the data for symbol = " + stockName + ", The tick sequence was at " + counter + ".");
				} catch (Exception e)
				{
					logger.warn("Please verify that TickDataQueue status. It seems pushing data to this queue produced an exception. The current of the queue = "
							+ TickDataQueue.getTickDataQueue().size());
					logger.warn("The capacity of the TickDataQueue is =" + TickDataQueue.getTickDataQueue().remainingCapacity());
				}
			}
		}
	}

	static void printCsvHeader()
	{
		// System.out.println(
		// "tickSequence,exchangeName,stockName,highPrice,lifeTimeHighPrice,lifeTimeLowPrice,dayHighPrice,lastTradedPrice,week52HighPrice,week52LowPrice,bestBidPrice,bestAskPrice,dayOpenPrice,dayClosePrice,prevDayClosePrice,dayLowPrice,highPriceRange,lowPriceRange,absolutePriceChange,percentPriceChange,bestBidQuantity,bestAskQuantity,dayVolume,date,lastTradedTime");
		logger.info(
				"tickSequence,exchangeName,stockName,highPrice,lifeTimeHighPrice,lifeTimeLowPrice,dayHighPrice,lastTradedPrice,week52HighPrice,week52LowPrice,bestBidPrice,bestAskPrice,dayOpenPrice,dayClosePrice,prevDayClosePrice,dayLowPrice,highPriceRange,lowPriceRange,absolutePriceChange,percentPriceChange,bestBidQuantity,bestAskQuantity,dayVolume,date,lastTradedTime");
	}

}
