#!/bin/bash

backupcwd=$PWD
cwd=$PWD
if [ $cwd != "/home/anand/repogit/java/eclipse/MarketDataClients/deploy" ]; then
	cd /home/anand/repogit/java/eclipse/MarketDataClients/deploy
	cwd=$PWD
fi

nohup ~/runq5000 $cwd/kdb/icici-init.q &
nohup java -jar $cwd/MarketDataClient.jar &
cd $backupcwd
