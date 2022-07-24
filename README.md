# TimeHook

A DLL library that hooks GetSystemTime to override the current time in an application.

## Usage

1. Create C:\timehook.ini and paste the sample configuration below
2. Inject the DLL into the process using an injector

## Sample Configuration File

    [Time]
    year=2022
    month=7
    day=24
    hour=11
    minute=28
    second=30