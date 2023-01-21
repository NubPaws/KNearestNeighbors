#include <memory>

#include "CommandLineInterface.h"
#include "CommandClasses.h"
#include "StringUtils.h"

CommandLineInterface::CommandLineInterface(DefaultIO* io)
	: io(io), knn(), train(), test() {
	
}

static std::string getWelcomeScreenMessage() {
	return "Welcome to the KNN Classifier Server. Please choose an option:\n"
		"1. upload an unclassified csv data file\n"
		"2. algorithm settings\n"
		"3. classify data\n"
		"4. display results\n"
		"5. download results\n"
		"8. exit\n";
}

void CommandLineInterface::start() {
	std::string clientInput;
	int option = 0;
	
	do {
		io->write(getWelcomeScreenMessage());
		
		clientInput = io->read();
		
		if (clientInput == "") {
			io->write("invalid packet\n");
			continue;
		}
		
		if (!Utils::isInt(clientInput)) {
			io->write("invalid input\n");
			continue;
		}
		
		option = std::stoi(clientInput);
		
		switch (option) {
		case 1: {
			UploadFileCommand ufc(io, knn, train, test);
			ufc.execute();
			break;
		}
		case 2: {
			AlgorithmSettingsCommand asc(io, knn);
			asc.execute();
			break;
		}
		case 3: {
			ClassifyDataCommand cdc(io, knn, test);
			cdc.execute();
			break;
		}
		case 4: {
			DisplayResultsCommand drc(io, test);
			drc.execute();
			break;
		}
		case 5: {
			DownloadResultsCommand drc(io, test);
			drc.execute();
			break;
		}
		case 8:
			break;
		default:
			io->write("invalid input\n");
		}
		
	} while (option != 8);
	
}
