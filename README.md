# NineThirtyFour
## A Command line chart viewer
Tired of having to google the price of your favorite publically tradable company? Want to introduce the comfort and familiarity of your terminal into the wild unpredictability of the stock market? Now you can!

This application will display the stock chart of a publically traded company in over the course of the current day. If the markets are closed, it will show the stock chart of a company during the last trading day.

Note that this project is pretty new. Bug reports, feature requests, and pull requests are appreciated!

## Compilation
```
make
```

## Running
```
cd bin/
ninethirtyfour [Options]
```

## Options
```
-h    --help                                      Display this help page
-D    --debug        [TRACE/DEBUG/INFO/WARN/ERR]  Change Logging level
      --transparent                               makes charts transparent
-S    --save                                      Saves data shown in chart to disk
-L    --load         [Filename].stock             Load saved data 
-s    --security     [Stock ticker name]          Displays price chart of a company
-m    --mini                                      Makes chart very small
      --tty          [tty number]                 Prints out log data to a specified /dev/pts/
```
as of now if you run this application without specifying a stock it will default to AMD



## Planned features 
- Changing displayed equity at runtime
- Showing the price of options (If you follow OCC Option symbol format you can technically get a chart, but it's buggy)
- Filling in awkward gaps in a chart
- Easy option searching 
- Expand time range for chart viewing
- Changing the size of the chart to fit user's screen
- Header above graph to display information such as if the market is open
- 

_v0.1.2_
