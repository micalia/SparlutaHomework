#include <iostream>
#include <random>
#include <cassert>
using namespace std;

class Animal {
public:
	virtual ~Animal() { cout << "~Animal()" << endl; };
	virtual void makeSound() = 0;
};

class Dog : public Animal {
	~Dog() { cout << "~Dog()" << endl; }// 도전2 => 동물 객체가 동적으로 생성 및 해제되어 메모리 누수가 발생하지 않도록 구현했는지 확인
	void makeSound() {
		cout << "Woof" << endl;
	}
};

class Cat : public Animal {
	~Cat() { cout << "~Cat()" << endl; }// 도전2 => 동물 객체가 동적으로 생성 및 해제되어 메모리 누수가 발생하지 않도록 구현했는지 확인
	void makeSound() {
		cout << "Meow" << endl;
	}
};

class Cow : public Animal {
	~Cow() { cout << "~Cow()" << endl; }// 도전2 => 동물 객체가 동적으로 생성 및 해제되어 메모리 누수가 발생하지 않도록 구현했는지 확인
	void makeSound() {
		cout << "Moo"<< endl;
	}
};

class Zoo {
public:
	int assignCnt;// 공간 할당 갯수
	Zoo() {
		assignCnt = sizeof(animals) / sizeof(animals[0]); 
	}

private:
	Animal* animals[10] = {nullptr}; // 동물 객체를 저장하는 포인터 배열
public:

	// 동물을 동물원에 추가하는 함수
	   // - Animal 객체의 포인터를 받아 포인터 배열에 저장합니다.
	   // - 같은 동물이라도 여러 번 추가될 수 있습니다.
	   // - 입력 매개변수: Animal* (추가할 동물 객체)
	   // - 반환값: 없음
	int pivot = -1;
	/*
		도전1 => zoo 클래스의 addAnimal()함수가 요구사항에 따라 동물을 추가할수 있는지 확인
	*/
	void addAnimal(Animal* animal) {  // 동적할당된 주소
		++pivot;
		if (pivot < assignCnt) {
			animals[pivot] = animal;
		}
		else { // 
			--pivot;
		}
	}

	// 동물원에 있는 모든 동물의 행동을 수행하는 함수
   // - 모든 동물 객체에 대해 순차적으로 소리를 내고 움직이는 동작을 실행합니다.
   // - 입력 매개변수: 없음
   // - 반환값: 없음
	void performActions() {
		int i = 0;
		/*
		도전3 => zoo 클래스내에 제한된 크기의 animals 배열이 있는데 추가시 이 제한된 크기를 고려해서 적절하게 동적할 수 있도록 예외사항을 충분히 반영했는지 확인
		*/
		while (animals[i] != nullptr && i < assignCnt) {

			animals[i]->makeSound();

			++i;
		}
	}

	// Zoo 소멸자
// - Zoo 객체가 소멸될 때, 동물 벡터에 저장된 모든 동물 객체의 메모리를 해제합니다.
// - 메모리 누수를 방지하기 위해 동적 할당된 Animal 객체를 `delete` 합니다.
// - 입력 매개변수: 없음
// - 반환값: 없음
	/*
		도전1 => zoo 클래스의 소멸자가 모든 동적 할당된 객체를 메모리에서 올바르게 해제하는지 확인
	*/
	virtual ~Zoo(){ 
		cout << "~Zoo()============"<<endl; 
		int i = pivot;

		while (i >= 0) {
			delete animals[i];
			--i;
		}
		
	};
};

// 랜덤 동물을 생성하는 함수
// - 0, 1, 2 중 하나의 난수를 생성하여 각각 Dog, Cat, Cow 객체 중 하나를 동적으로 생성합니다.
// - 생성된 객체는 Animal 타입의 포인터로 반환됩니다.
// - 입력 매개변수: 없음
// - 반환값: Animal* (생성된 동물 객체의 포인터)
Animal* createRandomAnimal(){
	std::random_device rd;  // 시드 생성기
	std::mt19937 gen(rd());  // Mersenne Twister 엔진
	std::uniform_int_distribution<> dis(0, 2);  
	
	Animal* animPtr = nullptr;
	// 난수 생성
	int random_number = dis(gen);
	switch (random_number) {
		case 0 : //Dog
			animPtr = new Dog();
		break;
		case 1 :
			animPtr = new Cat();
		break;
		case 2 :
			animPtr = new Cow();
		break;
	}

	return animPtr;
};

int CreateCnt;
int main()
{
	cin >> CreateCnt;
	Zoo* zoo = new Zoo();
	
	for (int i = 0 ; i <CreateCnt; i++)
	{
		Animal* animal = createRandomAnimal();
		assert(animal != nullptr);
		zoo->addAnimal(animal);
	}

	zoo->performActions();
	delete zoo;
}
