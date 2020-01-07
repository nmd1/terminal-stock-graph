## Detail
- [NEW]       - Added feature
- [ISSUE]     - Found issues that have yet to be fixed
- [FIXED]     - Issue that has been fixed
- [UPDATE]    - Modified something that wasn't broken
- [NOTE]      - Something to keep in mind
- [WORKING]   - In the middle of coding, normally should be empty at commit

### [NEW]
- (debug) Counter for stock graph updates
- Catch2 has been added as a testing suite
- Basic tests of the point class has been added

### [UPDATE]
- Created new log file for changes instead of appending them at the end of 
the main file
- Make changed to support Catch2 tests
- Signal and debug file handler defined outside of main to support testing

### [ISSUE] 
- Graph misaligned and labels go missing on certain json data sets
- Tests unveiled issue with directed points and 3D points being treated as 2D

### [FIXED]
- Point class was giving direction values to 1D points
