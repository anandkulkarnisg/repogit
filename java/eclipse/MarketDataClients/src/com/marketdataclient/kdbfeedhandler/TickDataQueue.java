package com.marketdataclient.kdbfeedhandler;

import java.util.concurrent.BlockingQueue;

public class TickDataQueue
{
	private static BlockingQueue<String> tickDataQueue;

	public static BlockingQueue<String> getTickDataQueue()
	{
		return tickDataQueue;
	}

	public static void setTickDataQueue(BlockingQueue<String> dataQueue)
	{
		tickDataQueue = dataQueue;
	}

}
