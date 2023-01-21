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
	Option option = Option::Empty;
	
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
		
		option = (Option)std::stoi(clientInput);
		
		Command *cmd = nullptr;
		switch (option) {
		case Option::Upload:
			cmd = new UploadFileCommand(io, knn, train, test);
			break;
		case Option::Settings:
			cmd = new AlgorithmSettingsCommand(io, knn);
			break;
		case Option::Classifiy:
			cmd = new ClassifyDataCommand(io, knn, test);
			break;
		case Option::Display:
			cmd = new DisplayResultsCommand(io, test);
			break;
		case Option::Download:
			cmd = new DownloadResultsCommand(io, test);
			break;
		case Option::Exit:
			break;
		default:
			io->write("invalid input\n");
		}
		
		if (cmd != nullptr) {
			cmd->execute();
			delete cmd;
			cmd = nullptr;
		}
		
	} while (option != Option::Exit);
	
}
