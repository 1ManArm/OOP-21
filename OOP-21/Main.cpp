#include <iostream>
#include <string>
#include <vector>

#include <set>
#include <unordered_set>
#include <map>

#include <algorithm>

struct Record {
	int id;
	std::string name;
	double wage;

	bool operator<(const Record& obj)const {
		return id < obj.id;
	}
	bool operator==(const Record & obj)const {
		return id == obj.id && name == obj.name && wage == obj.wage;
	}

};

namespace std {
	template<>
	struct hash<Record> {
		size_t operator()(const Record& obj) {
			//взять хэш-функцию от первого поля
			//сдивнуть результат на 1 бит влево
			//взять хэш функцию от второго поля
			//побитовое "исключающие или" между результатом и последней хэш функцией
			using std::size_t;
			using std::hash;
			return (hash<int>()(obj.id) ^
				(hash<std::string>()(obj.name) << 1) ^
				(hash<double>()(obj.wage) << 1));;
		}
	};
}

void f00(){
	std::unordered_set<Record> coll;
	coll.insert(Record());
	std::map<int, Record> coll2;
	Record a{ 1, "Ivan", 1234.7 };
	coll2.insert(std::pair<int, Record>{ a.id, a });
}

int main() {
	setlocale(LC_ALL, "Russian");

	std::vector<int> data/*{ 12,45,65,7,6,8 }*/;
	data.reserve(10000);
	/*data.push_back(067);*/

	for (size_t i = 0; i < data.capacity(); i++) {
		data.emplace_back(::rand() % 10000);

	}

	//цикл прохода по массиву О(n)
	// цикл поиска повторений O(n)
	// изменение счетчика уникальных элементов
	std::set<int> uniq_elements;
	for (size_t i = 0; i < data.size(); i++) {
		uniq_elements.insert(data[1]);
	}

	/*for (auto& el : data)uniq_elements.insert(el);*/

	std::cout << data.size() << " All data\n" << uniq_elements.size() << " different data\n";

	std::vector<int> uniq_data;
	for (auto& el : data) {
		auto find = std::find(uniq_data.begin(), uniq_data.end(), el);
		if (find == uniq_data.end()) {
			uniq_data.push_back(el);
		}
	}

	std::cout << data.size() << " All data\n" << uniq_data.size() << " different data\n";

	std::vector<int> data_other;
	data_other.reserve(10000);
	for (size_t i = 0; i < data_other.capacity(); i++) {
		data_other.emplace_back(-5000 + ::rand() % 10000);
	}

	std::set<int> uniq_elements_other;
	for (size_t i = 0; i < data_other.size(); i++) {
		uniq_elements_other.insert(data_other[i]);
	}

	std::cout << data_other.size() << " All other data\n" << uniq_elements_other.size() << " different other data\n";

	std::vector<int> result;
	std::set_intersection(uniq_elements.begin(), uniq_elements.end(), uniq_elements_other.begin(), uniq_elements_other.end(), std::back_inserter(result));
	std::cout << result.size() << " intersect volume\n";
	
	return 0;
}