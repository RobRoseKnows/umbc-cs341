#include "PinHit.h"

PinHit::PinHit() : m_pin(-1), m_hits(0)
    { /* Empty constructor */ }

PinHit::PinHit(int key, int value) : m_pin(key), m_hits(value)
    { /* Empty constructor */ }

void PinHit::SetKey(int pin) {
    m_pin = pin;
}

int PinHit::GetKey() const {
    return m_pin;
}

int PinHit::GetValue() const {
    return m_hits;
}

void PinHit::IncrementHits() {
    m_hits++;
}

int PinHit::CompareTo(const PinHit& other) const {
    return m_hits - other.m_hits;
}

bool PinHit::operator==(const PinHit& other) {
    return m_pin == other.m_pin;
}

