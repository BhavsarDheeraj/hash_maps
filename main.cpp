#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

vector<int> removeDuplicates(int *arr, int size) {
  vector<int> output;
  unordered_map<int, bool> seen;
  for (int i = 0; i < size; i++) {
    if (seen.count(arr[i]) > 0) {
      continue;
    }
    seen[arr[i]] = true;
    output.push_back(arr[i]);
  }
  return output;
}

int highestFrequency(int *input, int n) {
  unordered_map<int, int> frequencies;
  for (int i = 0; i < n; i++) {
    frequencies[input[i]]++;
  }
  int maxCount = 1;
  int element = input[0];
  for (pair<int, bool> p : frequencies) {
    if (p.second > maxCount) {
      maxCount = p.second;
      element = p.first;
    }
  }
  return element;
}

void intersection(int input1[], int input2[], int size1, int size2) {
  unordered_map<int, int> frequencies1, frequencies2;
  if (size2 > size1) {
    int *temp = input1;
    input1 = input2;
    input2 = temp;
    swap(size1, size2);
  }
  for (int i = 0; i < size1; i++) {
    frequencies1[input1[i]]++;
  }
  for (int i = 0; i < size2; i++) {
    frequencies2[input2[i]]++;
  }
  for (pair<int, int> p : frequencies2) {
    if (frequencies1.count(p.first) > 0) {
      int freq = frequencies1.at(p.first);
      int times = min(p.second, freq);
      for (int i = 0; i < times; i++) {
        cout << p.first << endl;
      }
    }
  }
}

void PairSum(int *input, int n) {
  unordered_map<int, int> freqs;
  for (int i = 0; i < n; i++) {
    int number = input[i];
    if (freqs.count(number * -1) > 0) {
      int freq = freqs[number * -1];
      for (int j = 0; j < freq; j++)
        cout << abs(number) * -1 << ' ' << abs(number) << endl;
    }
    freqs[number]++;
  }
}

char *uniqueChar(char *str) {
  unordered_set<char> set;
  for (int i = 0; i < strlen(str); i++) {
    if (!(set.count(str[i]) > 0)) {
      set.insert(str[i]);
    }
  }
  char *out = new char[set.size()];
  int count = 0;
  for (int i = 0; i < strlen(str); i++) {
    if (set.find(str[i]) != set.end()) {
      out[count] = str[i];
      set.erase(str[i]);
      count++;
    }
  }
  out[count] = '\0';
  return out;
}

vector<int> longestConsecutiveIncreasingSequence(int *arr, int n) {
  unordered_map<int, int> ourMap;
  vector<int> ans;
  for (int i = 0; i < n; i++) {
    ourMap[arr[i]] = 1;
  }

  for (int i = 0; i < n; i++) {
    vector<int> temp;
    int current = arr[i];

    if (ourMap[current] == 0) {
      continue;
    }

    while (ourMap.count(current) > 0) {
      temp.push_back(current);
      ourMap[current] = 0;
      current++;
    }

    if (temp.size() > ans.size()) {
      ans = temp;
    }
  }
  return ans;
}

void printPairs(int *input, int n, int k) {
  unordered_map<int, int> map;
  for (int i = 0; i < n; i++) {
    map[input[i]]++;
  }
  for (pair<int, int> p : map) {
    int value = p.first;
    int freq = p.second;

    if (freq <= 0) continue;
    map[value] = 0;

    if (k == 0) {
      int count = value * (value - 1) / 2;
      for (int j = 0; j < count; j++) cout << value << " " << value << endl;
      continue;
    }

    int y = value - k;
    int yfreq = map[y];
    for (int j = 0; j < yfreq * freq; j++)
      cout << min(value, y) << " " << max(value, y) << endl;

    y = k + value;
    yfreq = map[y];
    for (int j = 0; j < yfreq * freq; j++)
      cout << min(value, y) << " " << max(value, y) << endl;
  }
}

int lengthOfLongestSubsetWithZeroSum(int *arr, int size) {
  unordered_map<int, int> sums;
  int maxLength = 0;
  int sum = 0;
  for (int i = 0; i < size; i++) {
    sum += arr[i];
    if (sums.count(sum) > 0) {
      int index = sums[sum];
      if (i - index > maxLength) {
        maxLength = i - index;
      }
    } else {
      sums[sum] = i;
    }
  }
  return maxLength;
}
