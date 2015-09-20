typedef struct Element Element;

struct Element {
	uint8_t index;
	uint8_t value;
	Element *next;
};

typedef struct Bag {
	uint8_t capacity;
	uint8_t size;
	uint8_t max;
	uint8_t min;
	Element *first;
} Bag;

Bag *Bag_create(uint8_t capacity) {
	Bag *bag = (Bag *) malloc(sizeof(Bag));
	bag->capacity = capacity;
	bag->size = 0;
	bag->max = 0;
	bag->min = 255;
	bag->first = NULL;
	
	return bag;
}

void Bag_addelement(Bag *bag, uint8_t val, uint8_t index) {
	assert(bag->size < bag->capacity);
	Element *new_element = (Element *)malloc(sizeof(Element));
	new_element->value = val;
	new_element->index = index;
	new_element->next = NULL;
	if (bag->first == NULL) {
		bag->first = new_element;
		bag->max = val;
		bag->min = val;
		bag->size = 1;
	} else {
		Element *element = bag->first;
		while(element->next != NULL) {
			element = element->next;
		}
		element->next = new_element;
		bag->size++;
	}
	
	if (val > bag->max) {
		bag->max = val;
	}
	if (val < bag->min) {
		bag->min = val;
	}
}

void Bag_removemax(Bag *bag) {
	if (bag->size == 0) {return;}
	Element *prev_element = NULL;
	Element *element = bag->first;
	uint8_t max = 0;
	while(element->value != bag->max) {
		if (element->value > max) {max = element->value;}
		prev_element = element;
		element = element->next;
	}
	if (prev_element == NULL) {
		bag->first = element->next;
		prev_element = bag->first;
	} else {
		prev_element->next = element->next;
	}
	free(element);
	bag->size--;
	
	if (bag->size == 0) {
		bag->max = 0;
		return;
	} else {
		while (prev_element != NULL) {
			if (prev_element->value > max) {max = prev_element->value;}
			prev_element = prev_element->next;
		}
	}
	
	bag->max = max;
	
}

uint8_t Bag_pop(Bag *bag) {
	assert(bag->size > 0);
	
	Element *element = bag->first;
	uint8_t value = element->value;
	
	bag->first = element->next;
	bag->size--;
	free(element);
	
	return value;
}

