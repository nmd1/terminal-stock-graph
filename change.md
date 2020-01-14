## Detail
- [NEW]       - Added feature
- [ISSUES]     - Found issues that have yet to be fixed
- [FIXED]     - Issue that has been fixed
- [UPDATE]    - Modified something that wasn't broken
- [NOTE]      - Something to keep in mind
- [WORKING]   - In the middle of coding, normally should be empty at commit

### [NEW]
- Exception handling!
- Logs! Log to stderr, files, both, neither
- Right now data is logged to debug.log and to tty9 
### [UPDATE]
- header files are now .hpp files
- if all OHLC values are missing, don't bother adding the empty data to the vector
- 
### [ISSUES] 
- Tests unveiled issue with directed points and 3D points being treated as 2D
- Optimization: open curl object once
- Current price is misplaced on chart
- 
### [FIXED]
- Weird issues related to having a zero data point in the OHLC vector
### [WORKING]