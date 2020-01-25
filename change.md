## Detail
- [NEW]       - Added feature
- [ISSUES]     - Found issues that have yet to be fixed
- [FIXED]     - Issue that has been fixed
- [UPDATE]    - Modified something that wasn't broken
- [NOTE]      - Something to keep in mind
- [WORKING]   - In the middle of coding, normally should be empty at commit

### [NEW]
- Command line flags
  - `--help` will display the new options
  - Note: `-m` Does not do anything right now
  - `-s` will set which stock you want to view
- cmd data updates internal struct which other src files now depend on 
- Added way to convert string to long level


### [UPDATE]
- Default now does not log anything to any tty. Must explicity call flag
- README
  
### [ISSUES] 
- Tests unveiled issue with directed points and 3D points being treated as 2D
- Optimization: open curl object once
- Current price is misplaced on chart
- Size of graph is tied to terminal size
- No user feedback if incorrect stock is specified


### [FIXED]

### [WORKING]
