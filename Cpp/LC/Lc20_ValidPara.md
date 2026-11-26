# 20. Valid Parentheses (C++)

**Difficulty:** Easy | **Topics:** String, Stack

**Link:** https://leetcode.com/problems/valid-parentheses/

---

## Problem Description

Given a string `s` containing just the characters `'('`, `')'`, `'{'`, `'}'`, `'['` and `']'`, determine if the input string is **valid**.

An input string is valid if:
1. Open brackets must be closed by the **same type** of bracket.
2. Open brackets must be closed in the **correct order**.
3. Every close bracket has a corresponding open bracket of the same type.

**Example 1**
```
Input: s = "()"
Output: true
```

**Example 2**
```
Input: s = "()[]{}"
Output: true
```

**Example 3**
```
Input: s = "(]"
Output: false
```

**Example 4**
```
Input: s = "([])"
Output: true
```

**Constraints**
- `1 <= s.length <= 10^4`
- `s` consists of parentheses only: `'()[]{}'`

---

## Intuition and Key Insight

Brackets nest like a stack of plates: the **most recently opened** bracket must be the **first one closed**. That is last-in, first-out, so a stack is the natural structure.

- On an **open** bracket, push it.
- On a **close** bracket, the top of the stack must be its matching opener. If so, pop it. If the stack is empty or the top is a different type, the string is invalid.
- At the end, the stack must be **empty**, otherwise some opener was never closed.

**Pattern to recognize:** "matching or nested pairs, most recent first" → stack.

---

## Approaches

### 1. Brute Force: Repeatedly Remove Matched Pairs

```cpp
class Solution {
public:
    bool isValid(string s) {
        bool changed = true;
        while (changed) {
            changed = false;
            for (const string& pair : {"()", "[]", "{}"}) {
                size_t pos;
                while ((pos = s.find(pair)) != string::npos) {
                    s.erase(pos, 2);                // remove one matched pair
                    changed = true;
                }
            }
        }
        return s.empty();
    }
};
```

- **Time:** O(n²), since each find and erase is O(n) and up to n / 2 removals may be needed
- **Space:** O(1) extra, since it edits the local copy of `s`
- **Verdict:** Correct, but quadratic. Mention it as the baseline, then move to the stack.

### 2. Stack with a Close-to-Open Map (Optimal)

C++ translation of the Python solution from your notes.

```cpp
class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        unordered_map<char, char> closeToOpen = {
            {')', '('}, {']', '['}, {'}', '{'}
        };

        for (char c : s) {
            if (closeToOpen.count(c)) {                 // c is a closing bracket
                if (!st.empty() && st.top() == closeToOpen[c]) {
                    st.pop();                           // matched, discard the opener
                } else {
                    return false;                       // empty stack or wrong type
                }
            } else {
                st.push(c);                             // c is an opening bracket
            }
        }

        return st.empty();                              // leftover openers mean invalid
    }
};
```

- **Time:** O(n), one pass with O(1) work per character
- **Space:** O(n) in the worst case (for example all openers)
- **Verdict:** Optimal and the expected interview answer.

### 3. Stack Pushing the Expected Closer

```cpp
class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        for (char c : s) {
            if (c == '(') st.push(')');                 // push what we expect to see later
            else if (c == '[') st.push(']');
            else if (c == '{') st.push('}');
            else {
                if (st.empty() || st.top() != c) return false;
                st.pop();
            }
        }
        return st.empty();
    }
};
```

- **Time:** O(n)
- **Space:** O(n)
- **Verdict:** A compact variant with no map. Instead of comparing against the opener, you push the closer you are waiting for, so each closing character is compared directly with the top. C++ `pop()` returns nothing, so the top is read first and popped after.

### 4. Using a `string` as the Stack (Fastest in Practice)

```cpp
class Solution {
public:
    bool isValid(string s) {
        if (s.size() % 2) return false;                 // odd length can never pair up

        string st;                                      // string doubles as a stack
        st.reserve(s.size());
        for (char c : s) {
            if (c == '(' || c == '[' || c == '{') {
                st.push_back(c);
            } else {
                if (st.empty()) return false;
                char open = st.back();
                if ((c == ')' && open != '(') ||
                    (c == ']' && open != '[') ||
                    (c == '}' && open != '{')) {
                    return false;
                }
                st.pop_back();
            }
        }
        return st.empty();
    }
};
```

- **Time:** O(n)
- **Space:** O(n)
- **Verdict:** Avoids the `std::stack` deque overhead and the hash map, and includes the odd-length early exit. A micro-optimization, but a handy pattern.

---

## Complexity Summary

| Approach | Time | Space | Notes |
|---|---|---|---|
| Repeated erase | O(n²) | O(1) | Baseline |
| **Stack + close-to-open map** | **O(n)** | **O(n)** | **Optimal, standard** |
| Stack of expected closers | O(n) | O(n) | Compact, no map |
| String as stack | O(n) | O(n) | Fastest in practice |

---

## Walkthrough (Stack + Map)

`s = "([{}])"`

| c | Type | Stack before | Action | Stack after |
|---|---|---|---|---|
| ( | open | [] | push | [ ( ] |
| [ | open | [ ( ] | push | [ (, [ ] |
| { | open | [ (, [ ] | push | [ (, [, { ] |
| } | close | [ (, [, { ] | top `{` matches, pop | [ (, [ ] |
| ] | close | [ (, [ ] | top `[` matches, pop | [ ( ] |
| ) | close | [ ( ] | top `(` matches, pop | [] |

Stack is empty at the end, so the answer is `true`.

Failing cases:
- `"(]"`: at `]` the top is `(`, which is not `[`, so return `false`.
- `"(("`: the loop finishes with two openers left, so return `false`.
- `"))"`: the first `)` finds an empty stack, so return `false`.

---

## Why It Works

At any moment the stack holds exactly the openers that are still waiting to be closed, in the order they were opened. A valid string requires each closer to match the **innermost** unclosed opener, which is the top of the stack. So the check at each closer is both necessary and sufficient. The final empty-stack check catches openers that never found a closer.

---

## C++ Specific Notes

- **Check `empty()` before `top()`:** calling `top()` or `pop()` on an empty `std::stack` is undefined behavior, not an exception. Python raises `IndexError`, but C++ may crash or return garbage. The `!st.empty() &&` short-circuit is essential.
- **`pop()` returns void:** unlike Python's `list.pop()`, `std::stack::pop()` returns nothing. Read `top()` first, then `pop()`.
- **`closeToOpen[c]` with `operator[]`:** safe here because `c` was already confirmed to be a key via `count`. On a missing key it would insert a default value.
- **`count` vs `find`:** `closeToOpen.count(c)` is a clean membership test. For a map this small, a plain `switch` or `if` chain (approach 3 or 4) is faster than hashing.
- **`std::stack` uses `deque` by default:** `stack<char, vector<char>>` or a `string` (approach 4) is lighter.
- **Pass by value vs reference:** LeetCode's signature takes `string s` by value, which copies. In your own code, `const string& s` avoids the copy (except for approach 1, which edits `s`).
- **Brute force `for (const string& pair : {"()", "[]", "{}"})`:** iterates over an initializer list of `const char*`, converted to `string` on each iteration.
- **`size_t pos` and `string::npos`:** `find` returns `npos` when nothing is found, so compare against it, never against -1 stored in an `int`.
- **Includes:** `<stack>`, `<unordered_map>` and `<string>`. LeetCode includes them, but add them in your own setup.

---

## Edge Cases and Pitfalls

- **Closer with an empty stack** (`")"`): must return `false`. Skipping the `empty()` check before `top()` is undefined behavior in C++.
- **Leftover openers** (`"(("`): the loop ends normally, so the final `st.empty()` check is essential.
- **Right count, wrong order** (`")("`): same number of each, still invalid, because the closer comes first.
- **Right count, wrong type** (`"([)]"`): invalid because the `)` meets `[` on top of the stack.
- **Odd length:** always invalid.
- **Single character:** always invalid, because it is either an unmatched opener or closer.
- **Only counting each bracket type:** a counter per type fails on `"([)]"`. Order matters, so you need a stack.

---

## Interview Follow-Ups

- **"Only one bracket type?"** A single counter is enough. Increment on `(`, decrement on `)`, fail if it goes negative, and require 0 at the end (O(1) space).
- **"Return the index of the first error?"** Push indices alongside the brackets, and return the index of the failing closer or the bottom-most leftover opener.
- **"Minimum insertions or removals to make it valid?"** Track unmatched closers and leftover openers (LC 921, LC 1249).
- **"Longest valid substring?"** Stack of indices or DP (LC 32).
- **"What if other characters can appear?"** Ignore characters that are not brackets.
- **"Generate all valid strings?"** Backtracking, LC 22.
- **"Can you do better than O(n) space?"** Not for multiple bracket types in general. With one type, a counter gives O(1).

---

## Related Problems

- **22. Generate Parentheses:** generate all valid strings
- **32. Longest Valid Parentheses:** longest valid substring
- **921. Minimum Add to Make Parentheses Valid:** counting
- **1249. Minimum Remove to Make Valid Parentheses:** stack of indices
- **678. Valid Parenthesis String:** with wildcards, greedy range
- **301. Remove Invalid Parentheses:** BFS or backtracking
- **150. Evaluate Reverse Polish Notation:** stack evaluation
- **739. Daily Temperatures:** monotonic stack
- **155. Min Stack:** stack design

---
