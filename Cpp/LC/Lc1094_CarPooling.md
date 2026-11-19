# 1094. Car Pooling (C++)

**Difficulty:** Medium | **Topics:** Array, Sorting, Heap (Priority Queue), Simulation, Prefix Sum

**Link:** https://leetcode.com/problems/car-pooling/

---

## Problem Description

There is a car with `capacity` empty seats. The vehicle only drives **east** (it cannot turn around and drive west).

You are given the integer `capacity` and an array `trips` where `trips[i] = [numPassengers_i, from_i, to_i]` indicates that the i-th trip has `numPassengers_i` passengers, and the locations to pick them up and drop them off are `from_i` and `to_i` respectively. The locations are given as the number of kilometers due east from the car's initial location.

Return `true` if it is possible to pick up and drop off all passengers for all the given trips, or `false` otherwise.

**Example 1**
```
Input: trips = [[2,1,5],[3,3,7]], capacity = 4
Output: false
```

**Example 2**
```
Input: trips = [[2,1,5],[3,3,7]], capacity = 5
Output: true
```

**Constraints**
- `1 <= trips.length <= 1000`
- `trips[i].length == 3`
- `1 <= numPassengers_i <= 100`
- `0 <= from_i < to_i <= 1000`
- `1 <= capacity <= 10^5`

---

## Intuition and Key Insight

The only question is: **at any point on the road, are there ever more than `capacity` passengers in the car?** Each trip adds passengers at `from` and removes them at `to`. Passengers who get off at a location free their seats **before** new ones board at that same location, so a trip occupying `[from, to)` is a half-open interval.

There are two natural ways to track the load:
- **Event simulation:** process pickups in order of location, and use a min-heap keyed by drop-off point to remove passengers who have already left.
- **Difference array (sweep line):** record `+n` at `from` and `-n` at `to`, then take a running sum across the road. Because locations are at most 1000, a fixed array works.

**Pattern to recognize:** "overlapping intervals with weights, is the maximum overlap within a limit" → sweep line or difference array, or sort plus a min-heap of end times. The same family covers Meeting Rooms II and My Calendar III.

---

## Approaches

### 1. Brute Force: Check the Load at Every Location

```cpp
class Solution {
public:
    bool carPooling(vector<vector<int>>& trips, int capacity) {
        for (int loc = 0; loc <= 1000; loc++) {
            int load = 0;
            for (const auto& t : trips) {
                if (t[1] <= loc && loc < t[2]) {    // trip is on board at loc
                    load += t[0];
                }
            }
            if (load > capacity) return false;
        }
        return true;
    }
};
```

- **Time:** O(n x L), where n is the number of trips and L = 1001 is the number of locations
- **Space:** O(1)
- **Verdict:** About 10^6 operations here, which passes. It is the baseline that shows the question being asked.

### 2. Sort + Min-Heap

C++ translation of the first Python solution from your notes.

```cpp
class Solution {
public:
    bool carPooling(vector<vector<int>>& trips, int capacity) {
        sort(trips.begin(), trips.end(),
             [](const vector<int>& a, const vector<int>& b) {
                 return a[1] < b[1];                // process pickups in order of start
             });

        // min-heap of (end, numPassengers) for trips currently on board
        priority_queue<pair<int, int>,
                       vector<pair<int, int>>,
                       greater<pair<int, int>>> minHeap;

        int curPass = 0;
        for (const auto& t : trips) {
            int numPass = t[0], start = t[1], end = t[2];

            while (!minHeap.empty() && minHeap.top().first <= start) {
                curPass -= minHeap.top().second;    // drop off everyone who has arrived
                minHeap.pop();
            }

            curPass += numPass;                     // pick up the new passengers
            if (curPass > capacity) return false;
            minHeap.push({end, numPass});
        }
        return true;
    }
};
```

- **Time:** O(n log n), for the sort plus n heap pushes and pops
- **Space:** O(n) for the heap
- **Verdict:** Correct, and the general-purpose version. It works for any coordinate range, because it only looks at the trips themselves.

### 3. Difference Array / Sweep Line (Optimal for These Constraints)

C++ translation of the second Python solution from your notes.

```cpp
class Solution {
public:
    bool carPooling(vector<vector<int>>& trips, int capacity) {
        int passChange[1001] = {0};                 // net passenger change at each location

        for (const auto& t : trips) {
            int numPass = t[0], start = t[1], end = t[2];
            passChange[start] += numPass;           // pick up
            passChange[end] -= numPass;             // drop off
        }

        int curPass = 0;
        for (int i = 0; i <= 1000; i++) {
            curPass += passChange[i];               // running load after events at i
            if (curPass > capacity) return false;
        }
        return true;
    }
};
```

- **Time:** O(n + L), where L = 1001 is the coordinate range
- **Space:** O(L), a fixed 1001-int array
- **Verdict:** Optimal here, and the simplest to code. Both the pickup and drop-off at the same location are folded into one net change, so the "drop before pickup" rule happens automatically.

### 4. Sort Events (Sweep Line Without a Fixed Range)

```cpp
class Solution {
public:
    bool carPooling(vector<vector<int>>& trips, int capacity) {
        vector<pair<int, int>> events;              // (location, delta)
        events.reserve(trips.size() * 2);
        for (const auto& t : trips) {
            events.push_back({t[1], t[0]});         // +num at pickup
            events.push_back({t[2], -t[0]});        // -num at drop-off
        }

        sort(events.begin(), events.end());         // ties: negative deltas sort first
        int load = 0;
        for (const auto& e : events) {
            load += e.second;
            if (load > capacity) return false;
        }
        return true;
    }
};
```

- **Time:** O(n log n)
- **Space:** O(n)
- **Verdict:** Same idea as the difference array without needing a bounded range. Sorting pairs puts `-num` before `+num` at the same location, which is exactly the "drop off before pickup" order we need.

---

## Complexity Summary

| Approach | Time | Space | Notes |
|---|---|---|---|
| Brute force | O(n x L) | O(1) | Baseline, passes here |
| **Sort + min-heap** | **O(n log n)** | **O(n)** | **General, no range assumption** |
| **Difference array** | **O(n + L)** | **O(L)** | **Optimal here, simplest** |
| Sorted events | O(n log n) | O(n) | General sweep line |

*Here n = number of trips and L = coordinate range (1001).*

---

## Walkthrough (Difference Array)

`trips = [[2,1,5],[3,3,7]]`, `capacity = 4`

Build `passChange`:

| Location | 1 | 3 | 5 | 7 |
|---|---|---|---|---|
| Change | +2 | +3 | -2 | -3 |

Sweep with a running load:

| i | passChange[i] | curPass | > 4? |
|---|---|---|---|
| 0 | 0 | 0 | No |
| 1 | +2 | 2 | No |
| 2 | 0 | 2 | No |
| 3 | +3 | **5** | **Yes, return false** |

With `capacity = 5` the load peaks at exactly 5 and never exceeds it, so the answer is `true`.

## Walkthrough (Heap)

`trips = [[2,1,5],[3,3,7]]`, `capacity = 4` (already sorted by start)

| Trip | Heap before | Popped? | curPass after pickup | Result |
|---|---|---|---|---|
| [2,1,5] | empty | none | 2 | push (5, 2) |
| [3,3,7] | (5,2) | 5 <= 3? No | 5 | 5 > 4, **return false** |

---

## Why It Works

**Difference array:** after adding `+n` at `from` and `-n` at `to`, the prefix sum at location `i` equals the total passengers whose trip satisfies `from <= i < to`. That is exactly the number of people in the car after all events at `i`. The load can only increase at a pickup point, so checking it after every location covers the maximum.

**Heap:** trips are processed in order of start, so at each pickup the heap holds exactly the trips still on board. Before adding the new group, everyone whose `end <= start` is removed. Then the load is what is in the car at that pickup, and that is the only place the load can rise.

**The `<=` in the heap condition:** a passenger with `end == start` of the new trip has already left, so their seat is free. Using `<` instead would wrongly keep them on board.

---

## C++ Specific Notes

- **`priority_queue` is a max-heap by default.** For a min-heap, pass the container type and `greater<>` as the third template argument, as in approach 2. Forgetting this is the most common C++ heap bug.
- **Pairs compare lexicographically**, so `pair<int,int>` as `(end, numPassengers)` orders by end first, which is what we want. This is also why sorting `(location, delta)` pairs puts drop-offs (negative deltas) before pickups at the same location.
- **Comparator parameters by `const&`:** taking `vector<int>` by value would copy two vectors per comparison and slow the sort badly.
- **Strict weak ordering:** the comparator uses `<`, never `<=`.
- **`int passChange[1001] = {0};`** zero-initializes the whole array. Without `= {0}`, a local array holds garbage.
- **Array size 1001, not 1000:** locations go up to 1000 inclusive, so a drop-off at 1000 needs index 1000.
- **Overflow:** the largest possible load is 1000 trips x 100 passengers = 10^5, which fits easily in `int`.
- **`priority_queue` has no iteration or clear:** you can only read `top()`, `pop()` and `push()`. That is all this problem needs.
- **Includes:** `<queue>` for `priority_queue`, `<algorithm>` for `sort`, `<functional>` for `greater`. LeetCode includes them, but add them in your own setup.
- **Input is mutated** by `sort` in approaches 2, since the signature takes a non-const reference. Copy first if that matters.

---

## Edge Cases and Pitfalls

- **Drop-off and pickup at the same location** (`{{3,0,5},{3,5,8}}`, capacity 3): answer is `true`. The heap must use `<=`, and the difference array handles it automatically by netting the changes.
- **Single trip over capacity** (`{{9,0,1}}`, capacity 8): `false`.
- **Single trip within capacity:** `true`.
- **Trips that never overlap:** the load never accumulates, so `true`.
- **Locations up to 1000 inclusive:** the array must have size **1001**. A size-1000 array makes `passChange[1000]` an out-of-bounds write, which is undefined behavior in C++ (no exception, just silent corruption).
- **Check the load after every location in the difference array,** not only at the end, since the peak can be in the middle.
- **Early return inside the loop:** the heap version checks the capacity right after each pickup, which is the only moment the load can increase.
- **Wrong heap direction:** using the default max-heap would pop the latest drop-off first and break the logic.

---

## Interview Follow-Ups

- **"What if locations can be up to 10^9?"** The fixed array no longer fits. Use sorted events (approach 4) or the heap, both O(n log n), or coordinate compression.
- **"Which would you choose and why?"** The difference array here, because the range is only 1001 and it is simplest. The heap or sorted events if the range is large relative to n.
- **"What if the car can turn around, or has multiple stops in any order?"** It becomes a routing problem and is no longer an interval question.
- **"Return the location where the capacity is first exceeded."** In the sweep, return the index `i` at the first violation.
- **"What if passengers can be partially dropped or trips have priority?"** Track per-trip state in the heap and decide whom to remove.
- **"Count the maximum load at any time."** Return the maximum of the running sum (the Meeting Rooms II pattern, LC 253).
- **"Can you do better than O(n)?"** No, you must read every trip at least once.

---

## Related Problems

- **253. Meeting Rooms II:** maximum overlap using a heap or sweep line
- **252. Meeting Rooms:** detect any overlap
- **731. My Calendar II:** triple-booking check with a sweep or difference map
- **732. My Calendar III:** maximum overlap over time
- **1109. Corporate Flight Bookings:** difference array, the same technique
- **370. Range Addition:** difference array
- **435. Non-overlapping Intervals:** interval greedy with sorting
- **56. Merge Intervals:** sorting by start
- **218. The Skyline Problem:** sweep line with a heap

---
