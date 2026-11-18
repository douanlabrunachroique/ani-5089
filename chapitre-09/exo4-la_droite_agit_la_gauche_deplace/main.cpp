#include <iostream>
#include <string>
#include <sstream>
#include <unordered_set>

int main() {
    int n;
    if (!(std::cin >> n)) {
        return 0;
    }

    std::string dummy;
    std::getline(std::cin, dummy); // consume remainder of first line

    // Valid usages sets
    const std::unordered_set<std::string> left_usages = {
        "MENU", "MOVE", "SELECT_LEFT", "GRAB_LEFT", "AIM_POSE_LEFT", "GRIP_POSE_LEFT", "HAPTIC_LEFT"
    };

    const std::unordered_set<std::string> right_usages = {
        "SELECT", "GRAB", "AIM_POSE", "GRIP_POSE", "HAPTIC", "MOVE_RIGHT"
    };

    int deux_mains_total = 0;

    for (int i = 0; i < n; ++i) {
        std::string line;
        if (!std::getline(std::cin, line)) {
            break;
        }

        std::stringstream ss(line);
        std::string app_name;
        if (!(ss >> app_name)) {
            continue;
        }

        int right_count = 0;
        int left_count = 0;
        std::string token;

        while (ss >> token) {
            if (left_usages.find(token) != left_usages.end()) {
                ++left_count;
            } else if (right_usages.find(token) != right_usages.end()) {
                ++right_count;
            }
            // Unknown usages are ignored
        }

        bool is_deux_mains = (right_count > 0 && left_count > 0);
        if (is_deux_mains) {
            ++deux_mains_total;
        }

        std::cout << app_name << ' ' << right_count << ' ' << left_count << ' '
                  << (is_deux_mains ? "DEUX MAINS" : "UNE MAIN") << '\n';
    }

    std::cout << "DEUX MAINS " << deux_mains_total << '\n';

    return 0;
}
