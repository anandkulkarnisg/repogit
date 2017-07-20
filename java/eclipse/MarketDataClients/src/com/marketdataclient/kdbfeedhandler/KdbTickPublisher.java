package com.marketdataclient.kdbfeedhandler;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import com.marketdataclient.TickDataQueue;

public class KdbTickPublisher implements Runnable
{
	private ICICIFeedHandler feedHandler;
	final static Logger logger = LogManager.getLogger(KdbTickPublisher.class);

	public KdbTickPublisher()
	{
		try
		{
			feedHandler = new ICICIFeedHandler("localhost", 5000);
		} catch (Exception e)
		{

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
					csvTickItem = TickDataQueue.getTickDataQueue().take();
					boolean publishStatus = feedHandler.publish(csvTickItem);
					if (!publishStatus)
					{
						logger.warn("Failed to publish the below tick to the database. Please verify the content of the same. Below is its dump");
						logger.warn(csvTickItem);
					}

				} catch (InterruptedException e)
				{
					e.printStackTrace();
				}
			} catch (Exception e)
			{

			}

		}

	}
}
