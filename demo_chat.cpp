#include <iostream>
#include <string>
#include <vector>
#include <map>

// Giả lập câu trả lời của AI
std::map<std::string, std::string> simulatorResponses = {
    {"con trỏ", "Con trỏ là biến lưu địa chỉ ô nhớ. Ví dụ:\nint x = 10;\nint* ptr = &x;\ncout << *ptr; // In ra 10"},
    {"class", "Class là bản thiết kế để tạo object. Ví dụ:\nclass Car {\nprivate:\n    int speed;\npublic:\n    void drive() { ... }\n};"},
    {"vector", "Vector là mảng động trong C++. Ví dụ:\nvector<int> nums = {1, 2, 3};\nnums.push_back(4);"},
    {"hello", "Xin chào! Tôi là chatbot hỗ trợ học lập trình. Bạn có thể hỏi về C++, thuật toán, OOP..."},
    {"default", "Xin lỗi, tôi chưa có thông tin về câu hỏi này. Hãy thử hỏi về: con trỏ, class, vector"}
};

// Hàm giả lập AI
std::string simulatorAI(const std::string& question) {
    // Tìm keyword trong câu hỏi
    for (const auto& pair : simulatorResponses) {
        if (question.find(pair.first) != std::string::npos) {
            return pair.second;
        }
    }
    return simulatorResponses["default"];
}

int main() {
    std::cout << "╔════════════════════════════════════════════════════════════════════╗\n";
    std::cout << "║   DEMO LOCAL CHATBOT                                               ║\n";
    std::cout << "║   Gõ 'exit' để thoát, 'help' để xem gợi ý các câu lệnh được hỗ trợ ║\n";
    std::cout << "╚════════════════════════════════════════════════════════════════════╝\n\n";
    
    std::vector<std::pair<std::string, std::string>> history; // Lưu lịch sử
    std::string input;
    
    while (true) {
        std::cout << "👤 Bạn: ";
        std::getline(std::cin, input);
        
        // Xử lý lệnh
        if (input == "exit") {
            std::cout << "👋 Tạm biệt!\n";
            break;
        }
        
        if (input == "help") {
            std::cout << "💡 Bạn có thể hỏi về:\n";
            std::cout << "   - Con trỏ trong C++\n";
            std::cout << "   - Class và Object\n";
            std::cout << "   - Vector trong C++\n";
            std::cout << "   - Hoặc gõ 'history' để xem lịch sử\n\n";
            continue;
        }
        
        if (input == "history") {
            std::cout << "📜 Lịch sử hội thoại:\n";
            for (const auto& msg : history) {
                std::cout << "  👤: " << msg.first << "\n";
                std::cout << "  🤖: " << msg.second << "\n\n";
            }
            continue;
        }
        
        if (input == "clear") {
            history.clear();
            std::cout << "✅ Đã xóa lịch sử\n\n";
            continue;
        }
        
        if (input.empty()) continue;
        
        // Giả lập "đang suy nghĩ..."
        std::cout << "🤖 AI: ";
        std::cout.flush();
        
        // Lấy câu trả lời giả lập
        std::string answer = simulatorAI(input);
        
        // Giả lập streaming (in từng chữ)
        for (char c : answer) {
            std::cout << c << std::flush;
            // Bỏ comment dòng dưới để thấy hiệu ứng streaming rõ hơn
            // std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }
        std::cout << "\n\n";
        
        // Lưu vào lịch sử
        history.push_back({input, answer});
    }
    
    return 0;
}