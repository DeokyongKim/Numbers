#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <set>

#define MAX_DOMAIN 310
#define MAX_N 50010
#define INF 0x7fffffff

using namespace std;

map<string, int> domainToIndex;
int domainCnt = 1;

struct TASK {
  int requestTime;
  int priority;
  string requestUrl;

  bool operator < (const TASK& task) const {
    if (priority == task.priority) return requestTime > task.requestTime;
    return priority > task.priority;
  }
};

priority_queue<TASK> requests[MAX_DOMAIN];
set<string> requestUrls;

priority_queue<int, vector<int>, greater<int> > spareJudgers;

struct JUDGEINFORMATION {
  int start;
  int end;
  bool judging;
};
JUDGEINFORMATION history[MAX_DOMAIN];

int judgingDomainIndex[MAX_N];

string getDomain(string url) {
  return url.substr(0, url.find("/"));
}

void setJudgers(int n) {
  for (int i = 1; i <= n; i++) {
    spareJudgers.push(i);
    judgingDomainIndex[i] = -1;
  }
}

bool postRequest(TASK task) {
  string domain = getDomain(task.requestUrl);

  if (!requestUrls.count(task.requestUrl)) {
    requests[domainToIndex[domain]].push(task);
    requestUrls.insert(task.requestUrl);
    return true;
  }
  return false;
}

void requestJudge(TASK task) {
  string domain = getDomain(task.requestUrl);

  if (!domainToIndex[domain]) {
    domainToIndex[domain] = domainCnt++;
    
    history[domainToIndex[domain]] = {
      INF,
      INF,
      false,
    };

    // cout << domain << " IS NEW!\n";
  }

  postRequest(task);
}

bool isDDOS(int domainIndex, int requestTime) {
  if (history[domainIndex].start == INF) return false;

  int start = history[domainIndex].start;
  int end = history[domainIndex].end;
  int gap = end - start;

  // cout << "START: " << start << " END: " << end << "RT: " << requestTime << '\n';

  return requestTime < start + 3 * gap;
}

int getMostUrgentDomainIndex(int requestTime) {
  int targetIndex = -1;
  int minTime = INF;
  int minPriority = INF;

  for (int i = 1; i < domainCnt; i++) {
    // if (requests[i].empty()) cout << "NO REQUEST IN DOMAIN " << i <<'\n';
    // if (history[i].judging) cout << "JUDGING IN DOMAIN " << i <<'\n';
    // if (isDDOS(i, requestTime)) cout << "DDOS IN DOMAIN " << i <<'\n';

    if (!requests[i].empty() && !history[i].judging && !isDDOS(i, requestTime)) {
      int rt = requests[i].top().requestTime;
      int p = requests[i].top().priority;

      if (minPriority >= p) {
        if (minPriority > p) {
          targetIndex = i;
          minPriority = p;
          minTime = rt;
        } else if (minTime > rt) {
          targetIndex = i;
          minPriority = p;
          minTime = rt;
        }
      }
    }
  }

  return targetIndex;
}

void proceedJudge(int requestTime) {
  if (spareJudgers.empty()) return;

  int mostUrgentDomainIndex = getMostUrgentDomainIndex(requestTime);

  if (mostUrgentDomainIndex == -1) return;

  int judgerIndex = spareJudgers.top();
  spareJudgers.pop();

  TASK task = requests[mostUrgentDomainIndex].top();
  requests[mostUrgentDomainIndex].pop();
  requestUrls.erase(task.requestUrl);
  // cout << "PROCEED REQUEST! " << task.requestUrl << '\n';

  judgingDomainIndex[judgerIndex] = mostUrgentDomainIndex;
  history[mostUrgentDomainIndex].start = requestTime;
  history[mostUrgentDomainIndex].judging = true;
}

void endJudging(int requestTime, int judgerIndex) {
  if (judgingDomainIndex[judgerIndex] == -1) return;

  int domainIndex = judgingDomainIndex[judgerIndex];

  history[domainIndex].end = requestTime;
  history[domainIndex].judging = false;

  judgingDomainIndex[judgerIndex] = -1;

  spareJudgers.push(judgerIndex);

  // cout << "DOMAIN : " << domainIndex << "'s HISTORY: " << history[domainIndex].start << ", "<< history[domainIndex].end << ", "<< history[domainIndex].judging << "\n";
}

int getTaskNumberInRequests() {
  int ans = 0;
  for (int i = 1; i < domainCnt; i++) {
    ans += requests[i].size();
    // if (!requests[i].empty()) cout << requests[i].top().requestUrl << ' ';
  }
  // cout << ": ";
  return ans;
}

void getOrder() {
  int type;
  cin >> type;

  if (type == 100) {
    int N;
    string url;

    cin >> N >> url;

    setJudgers(N);
    requestJudge({0, 1, url});
  } else if (type == 200) {
    int requestTime, priority;
    string url;

    cin >> requestTime >> priority >> url;
    // cout << type << ": " << requestTime << '\n';

    requestJudge({requestTime, priority, url});
  } else if (type == 300) {
    int requestTime;
    cin >> requestTime;
    // cout << type << ": " << requestTime << '\n';
    
    proceedJudge(requestTime);
  } else if (type == 400) {
    int requestTime, judgerIndex;

    cin >> requestTime >> judgerIndex;
    // cout << type << ": " << requestTime << '\n';

    endJudging(requestTime, judgerIndex);
  } else if (type == 500) {
    int requestTime;
    cin >> requestTime;
    // cout << type << ": " << requestTime << '\n';

    cout << getTaskNumberInRequests() << '\n';
  }

  // cout << "REQUESTS: " << getTaskNumberInRequests() << '\n';
}

void getOrders() {
  int maxOrder;
  cin >> maxOrder;

  for (int i = 0; i < maxOrder; i++) {
    // cout << "\n\n NEW ORDER:\n";
    getOrder();
  }
}

int run() {
  getOrders();

  return 0;
}