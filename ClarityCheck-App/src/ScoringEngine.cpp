// ScoringEngine.cpp
// Design reference: DC-003 §3.2–3.4
// Boundary test cases defined in DC-003 §4; verified by DC-004 §6

#include "ScoringEngine.h"

// DC-003 §3.2 — ASRS v1.1 Part A scoring
// Shaded boxes per the published ASRS v1.1 Symptom Checklist:
// Items 1–3: positive if value >= 2 (Sometimes, Often or Very Often)
// Items 4–6: positive if value >= 3 (Often or Very Often)
// Positive screen if positiveCount >= 4
AsrsResult ScoringEngine::scoreAsrs(const QVector<int> &responses)
{
    AsrsResult result;
    for (int i = 0; i < 6 && i < responses.size(); ++i) {
        const int threshold = (i < 3) ? 2 : 3;
        if (responses[i] >= threshold)
            ++result.positiveCount;
    }
    result.positiveScreen = (result.positiveCount >= 4);
    return result;
}

// DC-003 §3.3 — PHQ-9 scoring
// Score = sum of all 9 item responses (0–3 each), range 0–27
// Crisis flag if item 9 (index 8) > 0
// Severity thresholds: 0–4 Minimal, 5–9 Mild, 10–14 Moderate, 15–19 Moderately Severe, 20–27 Severe
Phq9Result ScoringEngine::scorePhq9(const QVector<int> &responses)
{
    Phq9Result result;
    for (int i = 0; i < 9 && i < responses.size(); ++i)
        result.score += responses[i];

    if (responses.size() > 8)
        result.crisisFlag = (responses[8] > 0);

    if (result.score <= 4)
        result.category = QStringLiteral("MINIMAL");
    else if (result.score <= 9)
        result.category = QStringLiteral("MILD");
    else if (result.score <= 14)
        result.category = QStringLiteral("MODERATE");
    else if (result.score <= 19)
        result.category = QStringLiteral("MODERATELY_SEVERE");
    else
        result.category = QStringLiteral("SEVERE");

    return result;
}

// DC-003 §3.4 — GAD-7 scoring
// Score = sum of all 7 item responses (0–3 each), range 0–21
// Severity thresholds: 0–4 Minimal, 5–9 Mild, 10–14 Moderate, 15–21 Severe
Gad7Result ScoringEngine::scoreGad7(const QVector<int> &responses)
{
    Gad7Result result;
    for (int i = 0; i < 7 && i < responses.size(); ++i)
        result.score += responses[i];

    if (result.score <= 4)
        result.category = QStringLiteral("MINIMAL");
    else if (result.score <= 9)
        result.category = QStringLiteral("MILD");
    else if (result.score <= 14)
        result.category = QStringLiteral("MODERATE");
    else
        result.category = QStringLiteral("SEVERE");

    return result;
}
