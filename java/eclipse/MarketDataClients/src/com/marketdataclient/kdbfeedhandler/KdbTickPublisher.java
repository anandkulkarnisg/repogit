package com.marketdataclient.kdbfeedhandler;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import com.marketdataclient.kdbfeedhandler.TickDataQueue;

public class KdbTickPublisher implements Runnable
{
	private ICICIFeedHandler feedHandler;
	private String kdbServer;
	private int kdbPort;

	final static Logger logger = LogManager.getLogger(KdbTickPublisher.class);

	public KdbTickPublisher(String server, int port)
	{
		kdbServer = server;
		kdbPort = port;
		try
		{
			feedHandler = new ICICIFeedHandler(kdbServer, kdbPort);
		} catch (Exception e)
		{
			logger.fatal("Unable to make a connection to the kdb server at host -> " + kdbServer + " and port -> " + kdbPort + ". Exiting the application with failure status 1");
			System.exit(1);
		}
	}

	@Override
	public void run()
	{
		while (ICICIKdbTickPublisher.keepPublishing())
		{
			try
			{
				String csvTickItem = null;
				try
				{
					if (!TickDataQueue.getTickDataQueue().isEmpty())
					{
						csvTickItem = TickDataQueue.getTickDataQueue().take();
						boolean publishStatus = feedHandler.publish(csvTickItem);
						if (!publishStatus)
						{
							logger.warn("Failed to publish the below tick to the database. Please verify the content of the same. Below is its dump");
							logger.warn(csvTickItem);
						}
					}

				} catch (InterruptedException e)
				{
					logger.info("Got interrupted while waiting for the tick data in the queue.");
					e.printStackTrace();
				}
			} catch (Exception e)
			{
				logger.error("Exception occured while trying to publish the item from queue.Exception details are below");
				e.printStackTrace();
			}

		}

	}
}
