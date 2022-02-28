#include "FormList.h"

Form FormList::formList[FORM_COUNT];

void FormList::load(std::string fileName) {
    std::ifstream formListFileIn(fileName);
    if (!formListFileIn.good()) {
        formListFileIn.close();
        std::cout << "Creating forms...\n";
        std::ofstream formListFile(fileName);
        for (int letter = 0; letter < 26; letter++) {
            for (int place = 0; place < 5; place++) {
                for (int state = 0; state < 3; state++) {
                    formListFile << (char)(letter + 'a') << " " << place << " " << state << "\n";
                }
            }
        }
        formListFile.close();
    }

    std::cout << "Loading forms...\n";
    std::ifstream formListFile(fileName);
    std::string line;
    int i = 0;
    while (std::getline(formListFileIn, line)) {
        std::stringstream ss(line);
        ss >> formList[i].letter;
        ss >> formList[i].place;
        int a;
        ss >> a;
        formList[i].state = (State)a;
        i++;
    }
    i < FORM_COUNT ? throw std::runtime_error("Form data invalid") : NULL;

    formListFile.close();
    std::cout << "Done\n";
}