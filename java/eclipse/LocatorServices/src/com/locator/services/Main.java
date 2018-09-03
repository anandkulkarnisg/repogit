package com.locator.services;

public class Main
{
	public static void main(String[] args)
	{
		LocatorService locator = new LocatorService();
		System.out.println(locator.getIpaddress() + "," + locator.getCountry());
	}
}
