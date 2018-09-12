// We are given N different types of stickers. Each sticker has a lowercase
// English word on it.
//
// You would like to spell out the given target string by cutting individual
// letters from your collection of stickers and rearranging them.
//
// You can use each sticker more than once if you want, and you have infinite
// quantities of each sticker.
//
// What is the minimum number of stickers that you need to spell out the target?
// If the task is impossible, return -1.
//
// Example 1:
//
// Input:
//
// ["with", "example", "science"], "thehat"
// Output:
//
// 3
// Explanation:
//
// We can use 2 "with" stickers, and 1 "example" sticker.
// After cutting and rearrange the letters of those stickers, we can form the
// target "thehat". Also, this is the minimum number of stickers necessary to
// form the target string. Example 2:
//
// Input:
//
// ["notice", "possible"], "basicbasic"
// Output:
//
// -1
// Explanation:
//
// We can't form the target "basicbasic" from cutting letters from the given
// stickers. Note:
//
// stickers has length in the range [1, 50].
// stickers consists of lowercase English words (without apostrophes).
// target has length in the range [1, 15], and consists of lowercase English
// letters. In all test cases, all words were chosen randomly from the 1000 most
// common US English words, and the target was chosen as a concatenation of two
// random words. The time limit may be more challenging than usual. It is
// expected that a 50 sticker test case can be solved within 35ms on average.

class Solution {
public:
    int minStickers(vector<string>& stickers, string target) {
        int m = stickers.size();
        vector<vector<int>> dict(m, vector<int>(26, 0));
        for (int i = 0; i < stickers.size(); ++i) {
            for (auto c : stickers[i]) {
                dict[i][c - 'a']++;
            }
        }

        unordered_map<string, int> dp;
        dp[""] = 0;
        dfs(dp, dict, target);

        return dp[target];
    }

    int dfs(unordered_map<string, int>& dp,
            vector<vector<int>>& dict,
            string target) {
        if (dp.count(target)) {
            return dp[target];
        }
        int m = dict.size();
        int res = INT_MAX;

        vector<int> collect(26, 0);
        for (auto c : target) {
            collect[c - 'a']++;
        }

        for (int i = 0; i < m; ++i) {
            if (dict[i][target[0] - 'a'] == 0) {
                continue;
            }
            string s;
            for (int j = 0; j < 26; ++j) {
                if (collect[j] > dict[i][j]) {
                    s += string(collect[j] - dict[i][j], 'a' + j);
                }
            }
            if (s != target) {
                int temp = dfs(dp, dict, s);
                if (temp != -1) {
                    res = min(res, temp + 1);
                }
            }
        }

        dp[target] = res == INT_MAX ? -1 : res;
        return dp[target];
    }
};
