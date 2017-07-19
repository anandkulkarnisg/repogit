package com.marketdataclient;

import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

import org.apache.commons.configuration.ConfigurationException;
import org.apache.commons.configuration.XMLConfiguration;
import org.apache.commons.configuration.tree.ConfigurationNode;

public class MarketDataConfigManager
{
	private XMLConfiguration config;
	private static final String defaultConfigPath = System.getProperty("user.dir") + "/config/marketDataClientConfig.xml";
	private Map<String, String> configMap;

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
			e.printStackTrace();
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
			e.printStackTrace();
		}
	}

}
