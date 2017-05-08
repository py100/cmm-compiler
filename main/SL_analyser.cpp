#include <bits/stdc++.h>
#include "SL_grammer.cpp"
#include "signtable.cpp"
using namespace std;
#ifndef SL_ANALYSER_INC
#define SL_ANALYSER_INC

typedef Signtable::Type Type;

class Analyser {
public:
  int tmpCount;
  int lineCount;
  struct Command {
    int cmdType;
    string arg1, op, arg2, result;
    string tostr() {
      return result + "\t" + arg1 + '\t' + op + '\t' + arg2;
    }
    Command(int _cmdType, string _result, string _arg1, string _op, string _arg2) {
      cmdType = _cmdType;
      arg1 = _arg1;
      arg2 = _arg2;
      op = _op;
      result = _result;
    }
    Command(){}
  };
  struct Node {
    // for value : 0:int 1:char 2:float 3:string 4:void
    // for statement : 
    // 0: compound_statement
    // 1: expression_statement
    // 2: iteration_statement
    // 3: jump_statement
    // 4: selection_statement
    int val_type; 
    int signNameId;
    int lineNumber;
    string signName;
    string val;
    Type type;
    vector<Command> cmds;
    vector<string> vars;
    Node(string _name){
      val_type = -1;
      signNameId = -1;
      lineNumber = -1;
      signName = "null";
      val = "null";
      cmds.clear();
      vars.clear();
      signName = _name;
    }
    Node(){
      val_type = -1;
      signNameId = -1;
      lineNumber = -1;
      signName = "null";
      val = "null";
      cmds.clear();
      vars.clear();
    }
    void show() {
      fprintf(stderr, "Node: [%d], [%s], [%s], cmds[%d]\n", val_type, signName.c_str(), val.c_str(), (int)cmds.size());
      for (auto var : vars) {
        fprintf(stderr, "{%s},", var.c_str());
      }
      fprintf(stderr, "\n");
    }
  };
  vector< Command > commands;
  Command gencode(int cmdid, string result, string arg1, string op, string arg2) {
    return Command(cmdid, result, arg1, op, arg2);
    //commands.push_back(Command(cmdid, result, arg1, op, arg2));
    fprintf(stderr, "gencode : %d -- %s, %s, %s, %s\n", cmdid, result.c_str(), arg1.c_str(), op.c_str(), arg2.c_str());
  }

  string ntos(int n) {
    stringstream ss;
    if (n >=0 ) {
      ss << '+';
    }
    ss << n;
    return ss.str();
  }
  
  deque< Node > stack_node;
	deque< int > stack_state;
	deque< int > stack_symbol;

  void init() {
		stack_state.clear();
		stack_symbol.clear();
    stack_node.clear();
    tmpCount = 0;
    lineCount = 0;
  }
  void updateSignTable(Node& node) {
    return;
  }
  string getTempName() {
    stringstream ss;
    ss << "temp" << tmpCount++;
    return ss.str();
  }

	int analyse(vector< vector<int> >& table, vector< pair<int, string> >& bf, SL_grammer& grammer, int err) {
		for (int i = 0; i < bf.size(); i++) {
			printf("%d--", bf[i].first);
		}
		printf("\n");
		int END = grammer.END;
		printf("END = %d\n", END);
		stack_state.push_back(0);
		stack_symbol.push_back(END);
    stack_node.push_back(Node());

		for (int i = 0; i < bf.size(); i++) {
			int sm = stack_state.back();
			int a = bf[i].first;
      string attr = bf[i].second;
			if (table[sm][a] == err) {
				printf("error table (%d, %d, %d)\n", i, sm, a);
				return -1;
			}
			else if (table[sm][a] > 0) {
        Node node = shiftIn(a, attr);
 			  stack_state.push_back(table[sm][a]);
				stack_symbol.push_back(a);
        stack_node.push_back(node);
        node.show();
			}
			else if (table[sm][a] < 0) {
				// reduce by table[sm][a];
				fprintf(stderr, "--reduced by %d--\n", -table[sm][a]);
        int reduceid = -table[sm][a];
				grammer.showexp(-table[sm][a]);
        Node node = translate(reduceid);
				int pos = -table[sm][a];
				int len = grammer.exps[pos].right.size();
				int A = grammer.exps[pos].left;

				for (int j = 0; j < len; j++) {
					stack_state.pop_back();
					stack_symbol.pop_back();
          stack_node.pop_back();
				}
				stack_symbol.push_back(A);
				int gt = table[stack_state.back()][A];
				if (gt == err) {
					printf("error goto\n");
					return -1;
				}
				else {
					stack_state.push_back(gt);
          stack_node.push_back(node);
          node.show();
				}
				i--;
			}
			else {
				printf("!!!Accpted!!!\n");
        fprintf(stderr, "stack_size = %d\n", (int)stack_node.size());
        
        for (auto nd : stack_node) {
          fprintf(stderr, "%s\n", nd.signName.c_str());
        }
        FILE *fp_parser = fopen("parser.out", "w");
        for (auto cmd : stack_node[1].cmds) {
          fprintf(fp_parser, "%s\n", cmd.tostr().c_str());
        }
        fclose(fp_parser);
				return 0;
			}
		}
		return -2;
	}
  Node translate(int id) {
    int top = (int)stack_node.size()-1;
    Node node = stack_node[top];
    switch(id) {
      case 0:
        node.signName = "program'";
        node.cmds = stack_node[top].cmds;
        break;
      case 1:
        node.signName = "program";
        node.cmds = stack_node[top].cmds;
        break;
      case 2:
        node.signName = "main_declaration";
        node.cmds = stack_node[top].cmds;
        break;
      case 3:
        node.signName = "type_specifier";
        node.val_type = 4;
        node.cmds = stack_node[top].cmds;
        break;
      case 4:
        node.signName = "type_specifier";
        node.val_type = 1;
        node.cmds = stack_node[top].cmds;
        break;
      case 5:
        node.signName = "type_specifier";
        node.val_type = 0;
        node.cmds = stack_node[top].cmds;
        break;
      case 6:
        node.signName = "type_specifier";
        node.val_type = 2;
        node.cmds = stack_node[top].cmds;
        break;
      case 7: case 8: case 9: case 10:
        node.signName = "compound_statement";
        if (id == 8 || id == 9) {
          node.cmds = stack_node[top-1].cmds;
        }
        else if (id == 10) {
          node.cmds = stack_node[top-2].cmds;
          for (auto cmd : stack_node[top-1].cmds) {
            node.cmds.push_back(cmd);
          }
        }
        break;
      case 11: case 12:
        node.signName = "declare";
        break;
      case 13:
        node.vars = stack_node[top-1].vars;
        node.val_type = stack_node[top-2].val_type;
        /*
        for (auto var : node.vars) {
          fprintf(stderr, "{%s}, ", var.c_str());
        }
        fprintf(stderr, "\n");
        */
        //updateSignTable(node);
        break;
      case 14:
        node.vars = stack_node[top].vars;
        break;
      case 15:
        node.vars = stack_node[top-2].vars;
        node.vars.push_back(stack_node[top].signName);
        break;
      case 16:
        node.signName = stack_node[top].signName;
        node.vars.push_back(stack_node[top].signName);
        break;
      case 17:
        node.signName = stack_node[top-2].signName;
        node.val_type = stack_node[top].val_type;
        node.val = stack_node[top-2].val;
        node.vars.push_back(stack_node[top-2].signName);
        break;
      case 19: case 20: case 21: case 22:
        node = stack_node[top];
        break;
      case 23:
        node.signName = "stm_list";
        node.cmds = stack_node[top].cmds;
        break;
      case 24:
        node.signName = "stm_list";
        node.cmds = stack_node[top-1].cmds;
        for (auto cmd : stack_node[top].cmds) {
          node.cmds.push_back(cmd);
        }
        break;
      case 25: case 26: case 27: case 28: case 29:
        node.signName = "statement";
        node.val_type = stack_node[top].val_type;
        node.cmds = stack_node[top].cmds;
        break;
      case 30: case 31:
        node.signName = "exp_sts";
        node.val_type = 1;
        node.val = stack_node[top].val;
        if (id == 31) {
          node.cmds = stack_node[top-1].cmds;
        }
        break;
      case 32: {
        node.signName = stack_node[top].signName;
        node.val_type = stack_node[top].val_type;
        node.val = stack_node[top].val;
        node.cmds = stack_node[top].cmds;
        break;
      }
      case 33:
        node = stack_node[top];
        break;
      case 34:
        node.signName = stack_node[top-2].signName;
        node.val = stack_node[top].val;
        node.val_type = stack_node[top].val_type;
        
        node.cmds = stack_node[top].cmds;
        node.cmds.push_back(gencode(34, stack_node[top-2].signName,
            stack_node[top].signName, "null", "null"));

        //gencode(34, stack_node[top-2].signName, 
            //stack_node[top].signName, "null", "null");
        break;
      case 48:
        node = stack_node[top];
        break;
      case 49: case 50:
        //node.signName = "additive";
        node.signName = getTempName();
        node.val_type = stack_node[top-2].val_type;
        node.val = stack_node[top].val;
        node.cmds = stack_node[top].cmds;
        node.cmds.push_back(gencode(id, node.signName, 
            stack_node[top-2].signName, 
            stack_node[top-1].signName, 
            stack_node[top].signName));
        break;
      case 51:
        node = stack_node[top];
        break;
      case 52: case 53: case 54:
        //node.signName = "multive";
        node.signName = getTempName();
        node.val_type = stack_node[top-2].val_type;
        node.val = stack_node[top].val;
        node.cmds = stack_node[top].cmds;
        node.cmds.push_back(gencode(id, node.signName, 
            stack_node[top-2].signName,
            stack_node[top-1].signName,
            stack_node[top].signName));
        break;
      case 55: case 56:
        node = stack_node[top];
        break;
      case 57:
        node.cmds = stack_node[top-2].cmds;
        node.cmds.push_back(Command( -1,
              "if not",
              stack_node[top-2].signName,
              "jmp",
              ntos(stack_node[top].cmds.size()+2)));
        for (auto cmd :stack_node[top].cmds) {
          node.cmds.push_back(cmd);
        }
        node.cmds.push_back(Command( -2,
              "jmp",
              ntos(-stack_node[top].cmds.size() - stack_node[top-2].cmds.size() - 1),
              "null",
              "null"));
        break;
      case 63:
        node.cmds = stack_node[top-2].cmds;
        node.cmds.push_back(Command( -1, 
              "if not",
              stack_node[top-2].signName,
              "jmp",
              ntos(stack_node[top].cmds.size()+1)));
        for (auto cmd : stack_node[top].cmds) {
          node.cmds.push_back(cmd);
        }
        break;
      case 64:
        node.cmds = stack_node[top-4].cmds;
        node.cmds.push_back(Command( -1, 
              "if not",
              stack_node[top-4].signName,
              "jmp",
              ntos(stack_node[top-2].cmds.size()+2)
              ));
        for (auto cmd : stack_node[top-2].cmds) {
          node.cmds.push_back(cmd);
        }
        node.cmds.push_back(Command( -2, 
              "jmp",
              ntos(stack_node[top].cmds.size()+1),
              "null",
              "null"
              ));
        for (auto cmd : stack_node[top].cmds) {
          node.cmds.push_back(cmd);
        }
        break;
      default:
        node = stack_node[top];
        break;
    }
    return node;
  }

  Node shiftIn(int id, string attr) {
    Node node;
    node.signNameId = id;
    node.val = attr;
    node.signName = attr;
    return node;
  }
};

#endif
