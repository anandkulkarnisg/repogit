package com.marketdataclient.configmanager;

import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;
import org.apache.commons.configuration.ConfigurationException;
import org.apache.commons.configuration.XMLConfiguration;
import org.apache.commons.configuration.tree.ConfigurationNode;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

public class MarketDataConfigManager
{
	private XMLConfiguration config;
	private static final String defaultConfigPath = System.getProperty("user.dir") + "/resources/marketDataClientConfig.xml";
	private static Map<String, String> configMap;

	final static Logger logger = LogManager.getLogger(MarketDataConfigManager.class);

	public Map<String, String> getConfigMap()
	{
		return configMap;
	}

	private void loadConfigAsMap()
	{
		configMap = new ConcurrentHashMap<String, String>();
		ConfigurationNode node = config.getRootNode();
		for (ConfigurationNode c : node.getChildren("entry"))
		{
			String key = (String) c.getAttribute(0).getValue();
			String value = (String) c.getValue();
			configMap.put(key, value);
		}
		logger.info("Successfully Loaded " + configMap.size() + " items into the properties config file");
	}

	public MarketDataConfigManager()
	{
		try
		{
			config = new XMLConfiguration(defaultConfigPath);
			config.setValidating(true);
			loadConfigAsMap();
		} catch (ConfigurationException e)
		{
			logger.error("Error Loading XMLConfiguration for the properties file = " + defaultConfigPath);
			logger.error("The stack Trace is dumped below" + e.getStackTrace().toString());
		}
	}

	public MarketDataConfigManager(String configFilePath)
	{
		try
		{
			config = new XMLConfiguration(configFilePath);
			config.setValidating(true);
			loadConfigAsMap();
		} catch (ConfigurationException e)
		{
			logger.error("Error Loading XMLConfiguration for the properties file = " + configFilePath);
			logger.error("The stack Trace is dumped below" + e.getStackTrace().toString());
		}
	}

	public int getIntegerConfig(String key, int defaultValue)
	{
		String result = getConfigMap().get(key);
		int returnResult;
		if (result == null)
		{
			return (defaultValue);
		} else
		{
			try
			{
				returnResult = Integer.parseInt(result);
			} catch (NumberFormatException e)
			{
				return (defaultValue);
			}
		}
		return (returnResult);
	}

	public double getDoubleConfig(String key, double defaultValue)
	{
		String result = getConfigMap().get(key);
		double returnResult;
		if (result == null)
		{
			return (defaultValue);
		} else
		{
			try
			{
				returnResult = Double.parseDouble(result);
			} catch (NumberFormatException e)
			{
				return (defaultValue);
			}
		}
		return (returnResult);
	}

	public boolean getBooleanConfig(String key, boolean defaultValue)
	{
		String result = getConfigMap().get(key);
		boolean returnResult;
		if (result == null)
		{
			return (defaultValue);
		} else
		{
			returnResult = Boolean.parseBoolean(result);
		}
		return (returnResult);
	}

	public long getLongConfig(String key, long defaultValue)
	{
		String result = getConfigMap().get(key);
		long returnResult;
		if (result == null)
		{
			return (defaultValue);
		} else
		{
			try
			{
				returnResult = Long.parseLong(result);
			} catch (NumberFormatException e)
			{
				return (defaultValue);
			}
		}
		return (returnResult);
	}

	public String getStringConfig(String key, String defaultValue)
	{
		String result = getConfigMap().get(key);
		if (result == null)
		{
			return (defaultValue);
		} else
		{
			return (result);
		}
	}

	// public static class StringBar extends Bar<String> {
	// public String get() {
	// return "";
	// }
	// }

}
