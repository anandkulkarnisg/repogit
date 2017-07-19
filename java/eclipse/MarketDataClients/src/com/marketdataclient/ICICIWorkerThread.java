package com.marketdataclient;

import java.util.Map;
import java.util.concurrent.atomic.AtomicInteger;
import com.marketdataclient.ICICIResultParser.exchangeInfo;

public class ICICIWorkerThread implements Runnable
{
	private String stockName;
	static AtomicInteger atomicInteger = new AtomicInteger(0);
	static boolean printTickResults = true;
	static boolean isNSE = false;
	static boolean isBSE = false;

	public static boolean isBSE()
	{
		return isBSE;
	}

	public static void setBSE(boolean isBSE)
	{
		ICICIWorkerThread.isBSE = isBSE;
	}

	public static boolean isNSE()
	{
		return isNSE;
	}

	public static void setNSE(boolean isNSE)
	{
		ICICIWorkerThread.isNSE = isNSE;
	}

	public static boolean isPrintTickResults()
	{
		return printTickResults;
	}

	public static void setPrintTickResults(boolean printTickResults)
	{
		ICICIWorkerThread.printTickResults = printTickResults;
	}

	public ICICIWorkerThread(String name)
	{
		stockName = name;
		setAtomicInteger(atomicInteger.get() + 1);
	}

	public static int getAtomicInteger()
	{
		return atomicInteger.get();
	}

	public static void setAtomicInteger(int atomicInteger)
	{
		ICICIWorkerThread.atomicInteger.set(atomicInteger);
	}

	static boolean allThreadsFinished()
	{
		if (getAtomicInteger() == 0)
			return (true);
		else
			return (false);
	}

	@Override
	public void run()
	{
		ICICIPrices priceItem = new ICICIPrices(stockName);
		int counter = 0;
		while (counter < 1000)
		{
			Map<String, Object> streamResultMap = priceItem.streamPrices();
			if (!streamResultMap.isEmpty())
			{
				if (isPrintTickResults())
				{
					GenericUtils.printResults(streamResultMap, stockName, counter);
				} else
				{
					if (isNSE())
					{
						ICICIResultParser nseResultParser = new ICICIResultParser(streamResultMap, exchangeInfo.NSE);
						GenericUtils.csvFormatResultPrinter(nseResultParser, stockName, counter);
					}

					if (isBSE())
					{
						ICICIResultParser bseResultParser = new ICICIResultParser(streamResultMap, exchangeInfo.BSE);
						GenericUtils.csvFormatResultPrinter(bseResultParser, stockName, counter);

					}
				}
			} else
				counter = 1000;
			++counter;
		}

		setAtomicInteger(atomicInteger.get() - 1);
	}

}
