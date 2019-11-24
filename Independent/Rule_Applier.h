#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Rule
{
	public:
		Rule();
		void display();
};
class Flipper
{
	public:
		vector<string> states;
		int no_of_states;
		Rule rule;
		int state_no;
		int pos;
		Flipper(Rule obj);
		string getState();
		void createTransitionTable();
		string flip();
		void display();
};
int hashing(string str);
unordered_map<int,Flipper*> generateFlipperMap(string password,vector<Rule> rules);
void generate(string password,string pattern,vector<Rule> rules);
Rule generateRuleObjectFromRule(string rule);
void incrementFlippers(vector<unordered_map<int,Flipper*>::iterator>* flipper_container);
vector<string> applyRules(string pass,vector<Rule> rules);
vector<string> readRules(FILE* rulebook);
vector<string> RuleApplier(string password);
