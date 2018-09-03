package com.locator.services;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.MalformedURLException;
import java.net.URL;

public class URLStreamer
{

	private String urlText;
	private long length;
	private String[] urlTextArray;

	public URLStreamer(String url)
	{
		urlText = url;
		urlTextArray = new String[1000];
	}

	protected void getRawLiveStream(String urlString)
	{
		URL urlReader = null;
		try
		{
			urlReader = new URL(urlString);
		} catch (MalformedURLException e)
		{
			e.printStackTrace();
		}

		BufferedReader in = null;
		try
		{
			in = new BufferedReader(new InputStreamReader(urlReader.openStream()));
		} catch (IOException e)
		{
			e.printStackTrace();
		}

		String bufferString = null;
		int counter = 0;

		try
		{
			while ((bufferString = in.readLine()) != null)
			{
				if (!bufferString.isEmpty())
				{
					urlTextArray[counter] = bufferString;
					++counter;
				}
			}
		} catch (IOException e)
		{
			e.printStackTrace();
		}

		length = counter;

		try
		{
			in.close();
		} catch (IOException e)
		{
			e.printStackTrace();
		}
	}

	public String[] getRawTextStream()
	{
		getRawLiveStream(urlText);
		return urlTextArray;
	}

	public void printRawLiveStream()
	{
		getRawLiveStream(urlText);
		for (int i = 0; i < length; ++i)
			System.out.println(i + " --> " + urlTextArray[i]);
	}
}
