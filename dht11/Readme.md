TODO:

- Change so only update temp if more than .5C difference or so
- Enhance data collection to retry X times if invalid value is read
- Record min/max temps read, and display them
- Save data to DB
  - Redis setup information here:  https://pimylifeup.com/raspberry-pi-redis/
  - Alternatively, dump a CSV file every day or something
  - Write raw values or compressed records (start time, num reports, etc)
- Would be nice to have command line args for stuff like above
- Add UI for reporting

