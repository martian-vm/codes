#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

// Convert string to lowercase
string toLower(const string& s) {
    string result = s;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// Remove duplicate symptoms
vector<string> removeDuplicates(const vector<string>& symptoms) {
    set<string> unique(symptoms.begin(), symptoms.end());
    return vector<string>(unique.begin(), unique.end());
}

// Calculate match score
int matchScore(const vector<string>& user, const vector<string>& disease) {
    set<string> userSet(user.begin(), user.end());
    int score = 0;

    for (const auto& symptom : disease) {
        if (userSet.count(symptom)) {
            score++;
        }
    }
    return score;
}

int main() {
    vector<string> userSymptoms;
    string input;

    cout << "=========================================\n";
    cout << "       SMART MEDICAL EXPERT SYSTEM       \n";
    cout << "=========================================\n";

    cout << "\nEnter symptoms one by one (type 'done' to finish)\n";
    cout << "Examples: fever, cough, headache, chills\n\n";

    // Input loop
    while (true) {
        cout << "Symptom: ";
        cin >> input;

        input = toLower(input);

        if (input == "done") break;

        userSymptoms.push_back(input);
    }

    // Remove duplicates
    userSymptoms = removeDuplicates(userSymptoms);

    // Knowledge base
    map<string, vector<string>> diseases = {
        {"Flu", {"fever", "cough", "fatigue"}},
        {"COVID-19", {"fever", "cough", "loss_of_taste"}},
        {"Malaria", {"fever", "chills", "sweating"}},
        {"Dengue", {"fever", "rash", "joint_pain"}},
        {"Typhoid", {"fever", "headache", "abdominal_pain"}}
    };

    cout << "\nAnalyzing symptoms...\n";

    string bestDisease = "Unknown";
    int maxScore = 0;
    int totalSymptoms = 0;

    // Evaluate diseases
    for (const auto& d : diseases) {
        int score = matchScore(userSymptoms, d.second);

        if (score > maxScore) {
            maxScore = score;
            bestDisease = d.first;
            totalSymptoms = d.second.size();
        }
    }

    // Output results
    if (maxScore == 0) {
        cout << "\nDiagnosis: Unable to determine disease.\n";
    } else {
        double confidence = (double)maxScore / totalSymptoms * 100;

        cout << "\nMost probable disease: " << bestDisease << endl;
        cout << "Match score: " << maxScore << "/" << totalSymptoms << endl;
        cout << "Confidence: " << confidence << "%\n";
    }

    cout << "\n⚠️ Advice: This is not a medical diagnosis.\n";
    cout << "Please consult a qualified doctor.\n";

    return 0;
}
