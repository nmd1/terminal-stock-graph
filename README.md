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
ninethirtyfour [Ticker Name]
```

as of now if you run this application without specifying a stock it will default to AMD

## Planned features 
- Changing displayed equity at runtime
- Showing the price of options (If you follow OCC Option symbol format you can technically get a chart, but it's buggy as of now)
- Filling in awkward gaps in a chart
- Easy option searching 
- Expand time range for chart viewing