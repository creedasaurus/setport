# Setport App

###~~~ setport v0.1.0a ~~~

File/Folder structure:

``` 
setport/
├── src/
│   ├── setport.cpp
│   ├── testing-setport.cpp
|
├── bin/
│   ├── setport (once created)
│   ├── testing-setport (once created)
|
├── txt/
│   ├── setport.about_en.txt
│   ├── setport.usage_en.txt
|
├── README.txt
├── install.sh
```

Instructions for install:
-------
1. Navigate to directory with the install.sh script using the terminal.
2. Run the following command from the terminal with sudo: `sudo sh install.sh`
3. You may now run the setport program from anywhere in your environment


Uninstallation:
-------
1. Run the following command with sudo privileges:
	`sudo rm /usr/local/bin/setport`
2. Delete directory containing these program files.


Running Tests:
-------
1. navigate to the executable: bin/testing-setport
2. execute using `./bin/testing-setport`  OR  `./testing-setport`
