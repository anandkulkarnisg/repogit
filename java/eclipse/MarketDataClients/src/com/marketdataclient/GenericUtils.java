package com.marketdataclient;
import java.util.Map;
import org.joda.time.LocalDate;

public class GenericUtils
{
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
		String csvResult = counter + "," + exchangeName + "," + stockName + "," + highPrice + "," + lifeTimeHighPrice + "," + lifeTimeLowPrice + "," + dayHighPrice + "," + lastTradedPrice + ","
				+ week52HighPrice + "," + week52LowPrice + "," + bestBidPrice + "," + bestAskPrice + "," + dayOpenPrice + "," + dayClosePrice + "," + prevDayClosePrice + ","
				+ +dayLowPrice + "," + highPriceRange + "," + lowPriceRange + "," + absolutePriceChange + "," + percentPriceChange + "," + bestBidQuantity + "," + bestAskQuantity
				+ "," + dayVolume + "," + valueDate + "," + lastTradedTime;

		System.out.println(csvResult);

	}

	static void printCsvHeader()
	{
		System.out.println(
				"tickSequence,exchangeName,stockName,highPrice,lifeTimeHighPrice,lifeTimeLowPrice,dayHighPrice,lastTradedPrice,week52HighPrice,week52LowPrice,bestBidPrice,bestAskPrice,dayOpenPrice,dayClosePrice,prevDayClosePrice,dayLowPrice,highPriceRange,lowPriceRange,absolutePriceChange,percentPriceChange,bestBidQuantity,bestAskQuantity,dayVolume,date,lastTradedTime");

	}

}
