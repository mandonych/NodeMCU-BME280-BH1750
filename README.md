# NodeMCU-BME280-BH1750
---
Простая погодная станция на плате NodeMCU v3 с двумя недорогими датчиками. Станция умеет измерять температуру, атмосферное давление, влажность, освещенность и отправлять данные на сайт [Народный мониторинг](https://narodmon.ru/). 

За основу был взят код с [этого](http://arduinolab.pw/index.php/2015/12/30/datchik-temperatury-dlya-narodnogo-monitoringa-na-esp8266/) сайта и переписан под датчики, которые используются в моём проекте. Кроме сайта у автора есть также [канал на Youtube](https://www.youtube.com/channel/UCUjrgufq7KGvb1YTSkvcXnw). Советую, масса полезной информации по теме. Вот например [обзор датчика BME280](https://youtu.be/ATM9Vx5xtgo), который я использовал в этой метеостанции.

Код редактировался в редакторе [Atom](https://atom.io/). Для работы с платой NodeMCU прямо из редактора Atom необходимо дополнение [PlatformIO](https://platformio.org/). Для установки дополнения я использовал [этот гайд](http://docs.platformio.org/en/latest/ide/atom.html#installation).
