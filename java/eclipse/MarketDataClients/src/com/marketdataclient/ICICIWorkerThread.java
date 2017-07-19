package com.marketdataclient;

import java.util.Map;
import java.util.concurrent.atomic.AtomicInteger;
import com.marketdataclient.ICICIResultParser.exchangeInfo;

public class ICICIWorkerThread implements Runnable
{
	private String stockName;
	static AtomicInteger atomicInteger = new AtomicInteger(0);
	static boolean printTickResults = true;

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
				ICICIResultParser nseResultParser = new ICICIResultParser(streamResultMap, exchangeInfo.BSE);
				if (isPrintTickResults())
					GenericUtils.printResults(streamResultMap, stockName, counter);
				else
					GenericUtils.csvFormatResultPrinter(nseResultParser, stockName, counter);
			} else
				counter = 1000;
			++counter;
		}

		setAtomicInteger(atomicInteger.get() - 1);
	}

}
