package com.marketdataclient.kdbfeedhandler;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class ICICIKdbTickPublisher
{

	private int numPublisherThreads;
	private String kdbServer;
	private int kdbPort;

	ExecutorService executor = null;

	public ExecutorService getExecutor()
	{
		return executor;
	}

	private static boolean keepPublishing = false;

	public static boolean keepPublishing()
	{
		return keepPublishing;
	}

	public static void setKeepPublishing(boolean keepPublishing)
	{
		ICICIKdbTickPublisher.keepPublishing = keepPublishing;
	}

	public ICICIKdbTickPublisher(int numWorkers, String server, int port)
	{
		numPublisherThreads = numWorkers;
		if (executor == null)
			executor = Executors.newFixedThreadPool(numPublisherThreads);
		setKeepPublishing(true);
		kdbServer = server;
		kdbPort = port;
	}

	public void start()
	{
		for (int i = 0; i < numPublisherThreads; ++i)
		{
			Runnable publisher = new KdbTickPublisher(kdbServer, kdbPort);
			executor.execute(publisher);
		}
	}
}
