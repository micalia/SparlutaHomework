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
	~Dog() { cout << "~Dog()" << endl; }// ����2 => ���� ��ü�� �������� ���� �� �����Ǿ� �޸� ������ �߻����� �ʵ��� �����ߴ��� Ȯ��
	void makeSound() {
		cout << "Woof" << endl;
	}
};

class Cat : public Animal {
	~Cat() { cout << "~Cat()" << endl; }// ����2 => ���� ��ü�� �������� ���� �� �����Ǿ� �޸� ������ �߻����� �ʵ��� �����ߴ��� Ȯ��
	void makeSound() {
		cout << "Meow" << endl;
	}
};

class Cow : public Animal {
	~Cow() { cout << "~Cow()" << endl; }// ����2 => ���� ��ü�� �������� ���� �� �����Ǿ� �޸� ������ �߻����� �ʵ��� �����ߴ��� Ȯ��
	void makeSound() {
		cout << "Moo"<< endl;
	}
};

class Zoo {
public:
	int assignCnt;// ���� �Ҵ� ����
	Zoo() {
		assignCnt = sizeof(animals) / sizeof(animals[0]); 
	}

private:
	Animal* animals[10] = {nullptr}; // ���� ��ü�� �����ϴ� ������ �迭
public:

	// ������ �������� �߰��ϴ� �Լ�
	   // - Animal ��ü�� �����͸� �޾� ������ �迭�� �����մϴ�.
	   // - ���� �����̶� ���� �� �߰��� �� �ֽ��ϴ�.
	   // - �Է� �Ű�����: Animal* (�߰��� ���� ��ü)
	   // - ��ȯ��: ����
	int pivot = -1;
	/*
		����1 => zoo Ŭ������ addAnimal()�Լ��� �䱸���׿� ���� ������ �߰��Ҽ� �ִ��� Ȯ��
	*/
	void addAnimal(Animal* animal) {  // �����Ҵ�� �ּ�
		++pivot;
		if (pivot < assignCnt) {
			animals[pivot] = animal;
		}
		else { // 
			--pivot;
		}
	}

	// �������� �ִ� ��� ������ �ൿ�� �����ϴ� �Լ�
   // - ��� ���� ��ü�� ���� ���������� �Ҹ��� ���� �����̴� ������ �����մϴ�.
   // - �Է� �Ű�����: ����
   // - ��ȯ��: ����
	void performActions() {
		int i = 0;
		/*
		����3 => zoo Ŭ�������� ���ѵ� ũ���� animals �迭�� �ִµ� �߰��� �� ���ѵ� ũ�⸦ ����ؼ� �����ϰ� ������ �� �ֵ��� ���ܻ����� ����� �ݿ��ߴ��� Ȯ��
		*/
		while (animals[i] != nullptr && i < assignCnt) {

			animals[i]->makeSound();

			++i;
		}
	}

	// Zoo �Ҹ���
// - Zoo ��ü�� �Ҹ�� ��, ���� ���Ϳ� ����� ��� ���� ��ü�� �޸𸮸� �����մϴ�.
// - �޸� ������ �����ϱ� ���� ���� �Ҵ�� Animal ��ü�� `delete` �մϴ�.
// - �Է� �Ű�����: ����
// - ��ȯ��: ����
	/*
		����1 => zoo Ŭ������ �Ҹ��ڰ� ��� ���� �Ҵ�� ��ü�� �޸𸮿��� �ùٸ��� �����ϴ��� Ȯ��
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

// ���� ������ �����ϴ� �Լ�
// - 0, 1, 2 �� �ϳ��� ������ �����Ͽ� ���� Dog, Cat, Cow ��ü �� �ϳ��� �������� �����մϴ�.
// - ������ ��ü�� Animal Ÿ���� �����ͷ� ��ȯ�˴ϴ�.
// - �Է� �Ű�����: ����
// - ��ȯ��: Animal* (������ ���� ��ü�� ������)
Animal* createRandomAnimal(){
	std::random_device rd;  // �õ� ������
	std::mt19937 gen(rd());  // Mersenne Twister ����
	std::uniform_int_distribution<> dis(0, 2);  
	
	Animal* animPtr = nullptr;
	// ���� ����
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
