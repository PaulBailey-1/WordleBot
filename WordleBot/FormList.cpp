#include "FormList.h"

Form FormList::formList[FORM_COUNT];

void FormList::load(std::string fileName) {

    std::ifstream formListFileIn(fileName);

    if (!formListFileIn.good()) {

        std::cout << "Creating forms...\n";
        formListFileIn.close();
        std::ofstream formListFileOut(fileName);

        for (int letter = 0; letter < 26; letter++) {
            for (int place = 0; place < 5; place++) {
                for (int state = 0; state < 3; state++) {
                    formListFileOut << (char)(letter + 'a') << " " << place << " " << state << "\n";
                }
            }
        }

        formListFileOut.close();
        formListFileIn.open(fileName);
    }

    std::cout << "Loading forms...\n";
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

    formListFileIn.close();

    std::cout << "Done\n";
}