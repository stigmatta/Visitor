#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Processor;
class Hdd;
class Ram;

class IVisitor abstract
{
public:
	virtual void VisitProcessor(Processor* proc) abstract;
	virtual void VisitHdd(Hdd* hdd) abstract;
	virtual void VisitRam(Ram* ram) abstract;
};

class AbstractDevice abstract
{
	string Producer;
public:
	virtual void Accept(IVisitor* visitor)abstract;
	string GetProducer()
	{ 
		return Producer;
	}
	void SetProducer(string Producer)
	{
		this->Producer = Producer;
	}
};

class Processor: public AbstractDevice
{
	string Frequency;
	string CoreCount;
public:
	string GetFrequency()
	{
		return  Frequency;
	}
	void SetFrequency(string Frequency)
	{
		this->Frequency = Frequency;
	}
	string GetCoreCount()
	{
		return CoreCount;
	}
	void SetCoreCount(string CoreCount)
	{
		this->CoreCount = CoreCount;
	}
	void Accept(IVisitor* visitor) override
	{
		visitor->VisitProcessor(this);
	}
};

class Hdd: public AbstractDevice
{
	string Volume;
	string Type;
public:
	string GetVolume()
	{
		return Volume;
	}
	void SetVolume(string Volume)
	{
		this->Volume = Volume;
	}
	string GetType()
	{
		return Type;
	}
	void SetType(string Type)
	{
		this->Type = Type;
	}
	void Accept(IVisitor* visitor) override
	{
		visitor->VisitHdd(this);
	}
};

class Ram : public AbstractDevice
{
	int totalCapacity;
	int availableCapacity;
public:
	int GetTotal()
	{
		return totalCapacity;
	}
	void SetTotal(int total)
	{
		this->totalCapacity = total;
	}
	int GetAvailable()
	{
		return availableCapacity;
	}
	void SetAvailable(int available)
	{
		this->availableCapacity = available;
	}

	void Accept(IVisitor* visitor) override
	{
		visitor->VisitRam(this);
	}
};

// сериализатор в HTML
class HtmlVisitor : public IVisitor
{
public:
	void VisitProcessor(Processor* proc) override
	{
		ofstream out("Processor.html", ios::binary | ios::trunc | ios::out);
		string result = "<html><head></head><body>";
		result += "<table><tr><td>Property<td><td>Value</td></tr>";
		result += "<tr><td>Producer<td><td>" + proc->GetProducer() + "</td></tr>";
		result += "<tr><td>Frequency<td><td>" + proc->GetFrequency() + "</td></tr>";
		result += "<tr><td>CoreCount<td><td>" + proc->GetCoreCount() + "</td></tr></table>";
		result += "</body></html>";
		out.write(result.c_str(), result.size());
		out.close();
	}
	void VisitHdd(Hdd* hdd) override
	{
		ofstream out("Hdd.html", ios::binary | ios::trunc | ios::out);
		string result = "<html><head></head><body>";
		result += "<table><tr><td>Property<td><td>Value</td></tr>";
		result += "<tr><td>Producer<td><td>" + hdd->GetProducer() + "</td></tr>";
		result += "<tr><td>Type<td><td>" + hdd->GetType() + "</td></tr>";
		result += "<tr><td>Volume<td><td>" + hdd->GetVolume() + "</td></tr></table>";
		result += "</body></html>";
		out.write(result.c_str(), result.size());
		out.close();
	}

	void VisitRam(Ram* ram) override {
		ofstream out("Ram.html", std::ios::binary | std::ios::trunc | std::ios::out);
		string result = "<html><head></head><body>";
		result += "<table><tr><td>Property<td><td>Value</td></tr>";
		result += "<tr><td>Producer<td><td>" + ram->GetProducer() + "</td></tr>";
		result += "<tr><td>Total capacity<td><td>" + to_string(ram->GetTotal()) + "</td></tr>";
		result += "<tr><td>Available capacity<td><td>" + to_string(ram->GetAvailable()) + "</td></tr></table>";
		result += "</body></html>";
		out.write(result.c_str(), result.size());
		out.close();
	}
};

// сериализатор в XML
class XmlVisitor: public IVisitor
{
public:
	void VisitProcessor(Processor* proc) override
	{
		ofstream out("Processor.xml", ios::binary | ios::trunc | ios::out);
		string result = "<?xml version='1.0' encoding='UTF-8'?>";
		result += "<Processor><Producer>" + proc->GetProducer() + "</Producer>" +
			"<Frequency>" + proc->GetFrequency() + "</Frequency>" +
			"<CoreCount>" + proc->GetCoreCount() + "</CoreCount></Processor>";
		out.write(result.c_str(), result.size());
		out.close();
	}
	void VisitHdd(Hdd* hdd) override
	{
		ofstream out("Hdd.xml", ios::binary | ios::trunc | ios::out);
		string result = "<?xml version='1.0' encoding='UTF-8'?>";
		result += "<HDD><Producer>" + hdd->GetProducer() + "</Producer>" +
			"<Type>" + hdd->GetType() + "</Type>" +
			"<Volume>" + hdd->GetVolume() + "</Volume></HDD>";
		out.write(result.c_str(), result.size());
		out.close();
	}

	void VisitRam(Ram* ram) override {
		ofstream out("Ram.xml", std::ios::binary | std::ios::trunc | std::ios::out);
		string result = "<?xml version='1.0' encoding='UTF-8'?>";
		result += "<RAM><Producer>" + ram->GetProducer() + "</Producer>" +
			"<Total>" + to_string(ram->GetTotal()) + "</Total>" +
			"<Available>" + to_string(ram->GetAvailable()) + "</Available></RAM>";
		out.write(result.c_str(), result.size());
		out.close();
	}
};

class ConsoleVisitor : public IVisitor
{
public:
	void VisitProcessor(Processor* proc) override
	{
		cout << "Processor\n" << "Producer:" << proc->GetProducer() << "\n";
		cout << "Frequency: " << proc->GetFrequency() << "\n";
		cout << "Core count: " << proc->GetCoreCount() << "\n";
	}
	void VisitHdd(Hdd* hdd) override
	{
		cout << "HDD\n" << "Producer:" << hdd->GetProducer() << "\n";
		cout << "Type:" << hdd->GetType() << "\n";
		cout << "Volume:" << hdd->GetVolume() << "\n";
	}

	void VisitRam(Ram* ram) override {
		cout << "RAM\n" << "Producer:" << ram->GetProducer() << "\n";
		cout << "Total capacity:" << ram->GetTotal() << "\n";
		cout << "Available capacity:" << ram->GetAvailable() << "\n";
	}
};

class PC
{
	vector<AbstractDevice*> devices;
public:
	void Add(AbstractDevice* d)
	{
		devices.push_back(d);
	}
	void Remove(AbstractDevice* d)
	{
		auto iter = find(devices.begin(), devices.end(), d);
		if(iter != devices.end())
			devices.erase(iter);
	}
	void Accept(IVisitor* visitor)
	{
		for(AbstractDevice* d : devices)
			d->Accept(visitor);
	}
};

int main()
{
	PC* pc = new PC();
	Processor *p = new Processor;
	p->SetProducer("Intel");
	p->SetFrequency("3.5");
	p->SetCoreCount("4");
	pc->Add(p);
	Hdd *hdd = new Hdd;
	hdd->SetProducer("Western Digital");
	hdd->SetType("SATA III");
	hdd->SetVolume("2");
	pc->Add(hdd);
	Ram* ram = new Ram;
	ram->SetProducer("ElectraByte Memory Solutions");
	ram->SetTotal(16);
	ram->SetAvailable(13);
	pc->Add(ram);
	HtmlVisitor *html = new HtmlVisitor;
	pc->Accept(html);
	XmlVisitor *xml = new XmlVisitor;
	pc->Accept(xml);
	ConsoleVisitor* csl = new ConsoleVisitor;
	pc->Accept(csl);
	delete html;
	delete xml;
	delete hdd;
	delete p;
	delete pc;

	system("pause");
}
