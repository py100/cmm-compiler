#include <bits/stdc++.h>

using namespace std;


class Signtable {
  public:
    struct Type {
      // type = 0:int
      // type = 1:real
      // type = 2:signtable
      int type, count;
      Type(){}
      Type(int _type, int _count):type(_type), count(_count){}
    };

    struct Sign {
      string name;
      Type type;
      int offset;
      Signtable *table;
      Sign(string _name, Type _type, int _offset, Signtable *_table) {
        name = _name;
        type = _type;
        offset = _offset;
        table = _table;
      }
    };
    
    vector<Sign> signs;
    int offset, sign_table_id;
    Signtable *father_table;

    Signtable(Signtable* _father_table_id, int _id) {
      clear();
      sign_table_id = _id;
      father_table = _father_table_id;
    }
    void clear() {
      signs.clear();
      offset = 0;
    }

    bool enter(string _name, Type _type, Signtable* _table) {
      for (auto sign : signs) {
        if (sign.name == _name) return true;
      }
      signs.push_back(Sign(_name, _type, offset, _table));
      int size;
      switch(_type.type) {
        case 0: case 1:
          size = 4*_type.count;
          break;
        default:
          size = 0;
          break;
      }
      offset += size;
      return true;
    }
};

