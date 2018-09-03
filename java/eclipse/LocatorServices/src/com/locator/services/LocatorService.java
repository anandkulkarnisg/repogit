package com.locator.services;

public class LocatorService
{

	private String ipaddress;
	private long decimalRepresentation;
	private String asn;
	private String city;
	private String country;
	private String countryCode;
	private String isp;
	private String latitude;
	private String longtitude;
	private String organization;
	private String postalCode;
	private boolean isPrivateIpAddress;
	private String ptrResourceRecord;
	private boolean isReservedIpAddress;
	private String timeZoneInfo;
	private String localTime;

	public String getIpaddress()
	{
		return ipaddress;
	}

	public long getDecimalRepresentation()
	{
		return decimalRepresentation;
	}

	public String getASN()
	{
		return asn;
	}

	public String getCity()
	{
		return city;
	}

	public String getCountry()
	{
		return country;
	}

	public String getCountryCode()
	{
		return countryCode;
	}

	public String getISP()
	{
		return isp;
	}

	public String getLatitude()
	{
		return latitude;
	}

	public String getLongtitude()
	{
		return longtitude;
	}

	public String getOrganization()
	{
		return organization;
	}

	public String getPostalCode()
	{
		return postalCode;
	}

	public boolean isPrivateIpAddress()
	{
		return isPrivateIpAddress;
	}

	public boolean isReservedIpAddress()
	{
		return isReservedIpAddress;
	}

	public String getTimeZoneInfo()
	{
		return timeZoneInfo;
	}

	public String getLocalTime()
	{
		return localTime;
	}

	public LocatorService()
	{
		URLStreamer ipStreamer = new URLStreamer("http://whatismyipv6address.com/");
		String[] results = ipStreamer.getRawTextStream();
		String ipAddress = results[5].substring(86, 99);
		URLStreamer ipInforStreamer = new URLStreamer("https://ipaddress.ip-adress.com/" + ipAddress);
		String[] ipInfoStreamerResults = ipInforStreamer.getRawTextStream();
		ipInforStreamer.printRawLiveStream();		
		
//		309 --> <tr><th>IP Address</th><td>58.182.109.60</td></tr>
//		310 --> <tr><th>Decimal Representation</th><td>985034044</td></tr>
//		311 --> <tr><th><abbr title="Autonomous System Number">ASN</abbr></th><td>AS55430</td></tr>
//		312 --> <tr><th>City</th><td>Singapore</td></tr>
//		313 --> <tr><th>Country</th><td>Singapore</td></tr>
//		314 --> <tr><th>Country Code</th><td>SG</td></tr>
//		315 --> <tr><th><abbr title="Internet Service Provider">ISP</abbr></th><td>StarHub Cable Vision</td></tr>
//		316 --> <tr><th>Latitude</th><td>1.2855&deg; (1&deg; 17&prime; 7&Prime; N)</td></tr>
//		317 --> <tr><th>Longitude</th><td>103.8565&deg; (103&deg; 51&prime; 23&Prime; E)</td></tr>
//		318 --> <tr><th>Organization</th><td>StarHub Internet</td></tr>
//		319 --> <tr><th>Postal Code</th><td></td></tr>
//		320 --> <tr><th>Is Private IP Address</th><td>no</td></tr>
//		321 --> <tr><th>PTR Resource Record</th><td><a href="https://website.ip-adress.com/60.109.182.58.starhub.net.sg">60.109.182.58.starhub.net.sg</a></td></tr>
//		322 --> <tr><th>Is Reserved IP Address</th><td>no</td></tr>
//		323 --> <tr><th>State</th><td></td></tr>
//		324 --> <tr><th>State Code</th><td>00</td></tr>
//		325 --> <tr><th>Timezone</th><td></td></tr>
//		326 --> <tr><th>Local Time</th><td></td></tr>
		

		ipaddress = ipInfoStreamerResults[309].replace("<tr><th>IP Address</th><td>", "").replace("</td></tr>", "");
		decimalRepresentation = Long.parseLong(ipInfoStreamerResults[310].replace("<tr><th>Decimal Representation</th><td>", "").replace("</td></tr>", ""));
		asn = ipInfoStreamerResults[311].replace("<tr><th><abbr title=\"Autonomous System Number\">ASN</abbr></th><td>", "").replace("</td></tr>", "");
		city = ipInfoStreamerResults[312].replace("<tr><th>City</th><td>", "").replace("</td></tr>", "");
		country = ipInfoStreamerResults[313].replace("<tr><th>Country</th><td>", "").replace("</td></tr>", "");
		isp = ipInfoStreamerResults[315].replace("<tr><th><abbr title=\"Internet Service Provider\">ISP</abbr></th><td>", "").replace("</td></tr>", "");
		latitude = ipInfoStreamerResults[316].replace("<tr><th>Latitude</th><td>", "").replace("</td></tr>", "");
		longtitude = ipInfoStreamerResults[317].replace("<tr><th>Longitude</th><td>", "").replace("</td></tr>", "");
		organization = ipInfoStreamerResults[318].replace("<tr><th>Organization</th><td>", "").replace("</td></tr>", "");
		postalCode = ipInfoStreamerResults[319].replace("<tr><th>Postal Code</th><td>", "").replace("</td></tr>", "");
		isPrivateIpAddress = Boolean.parseBoolean(ipInfoStreamerResults[319].replace("<tr><th>Is Private IP Address</th><td>", "").replace("</td></tr>", "")
				.replace("yes", "true").replace("no", "false"));
		ptrResourceRecord = ipInfoStreamerResults[321].replace("<tr><th>PTR Resource Record</th><td>", "").replace("</td></tr>", "");
		
		isReservedIpAddress = Boolean.parseBoolean(ipInfoStreamerResults[321].replace("<tr><th>Is Reserved IP Address</th><td>", "").replace("</td></tr>", "")
				.replace("yes", "true").replace("no", "false"));
		timeZoneInfo = ipInfoStreamerResults[325].replace("<tr><th>Timezone</th><td>", "").replace("</td></tr>", "");
		localTime = ipInfoStreamerResults[326].replace("<tr><th>Local Time</th><td>", "").replace("</td></tr>", "");

	}

	public String getPtrResourceRecord()
	{
		return ptrResourceRecord;
	}

}
