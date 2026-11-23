// tst_appstate.cpp
//
// Unit tests for AppState state machine.
// Verifies DC-003 §7 state transition rules.
// Safety-critical tests: FT-SAFE-01 (crisis trigger), FT-SAFE-02 (crisis gate),
// FT-SAFE-03 (age gate).

#include <QtTest>
#include "AppState.h"

class TstAppState : public QObject
{
    Q_OBJECT

private slots:
    // FT-SAFE-03 — Age gate
    void welcomeScreen_initial();
    void ageGate_blocksAdvance();
    void ageGate_acknowledgeTransitions();

    // Instrument sequence
    void instrumentSequence_asrsToPHQ9();
    void instrumentSequence_phq9ToGAD7_noCrisis();
    void instrumentSequence_gad7ToResults();

    // FT-SAFE-01 — PHQ-9 item 9 crisis trigger
    void crisisTrigger_item9Zero_noFlag();
    void crisisTrigger_item9One_flagSet();
    void crisisTrigger_item9Two_flagSet();
    void crisisTrigger_item9Three_flagSet();

    // FT-SAFE-02 — Crisis acknowledgement gate
    void crisisGate_blocksResults();
    void crisisGate_acknowledgeReachesResults();

    // Scores
    void scores_nullBeforeResults();
    void scores_availableAfterResults();
    void scores_gad7UnavailableInCrisisPath();

    // canAdvance / response
    void canAdvance_falseWithoutResponse();
    void canAdvance_trueAfterResponse();
    void canAdvance_responseChangeAllowed();

private:
    // Drive all items of one instrument with a given response value.
    // Assumes we are already on the INSTRUMENT_INTRO screen for that instrument.
    void completeInstrument(AppState &s, int responseValue);

    // Drive ASRS, PHQ-9 items 1–8 (no item 9 yet), leaving us on item 9.
    void driveToPhq9Item9(AppState &s);

    // Drive all three instruments without triggering crisis (item 9 = 0).
    void completeFullBattery(AppState &s);
};

// ── Helpers ──────────────────────────────────────────────────────────────────

void TstAppState::completeInstrument(AppState &s, int responseValue)
{
    // Must be on INSTRUMENT_INTRO
    QCOMPARE(s.currentScreen(), QStringLiteral("INSTRUMENT_INTRO"));
    s.beginInstrument();
    QCOMPARE(s.currentScreen(), QStringLiteral("QUESTION"));

    const int count = s.sectionItemCount();
    for (int i = 0; i < count; ++i) {
        s.setCurrentResponse(responseValue);
        s.advance();
    }
}

void TstAppState::driveToPhq9Item9(AppState &s)
{
    // Start fresh
    s.acknowledgeAge();
    completeInstrument(s, 1);  // ASRS (all 6 items, response 1)

    // PHQ-9 — answer items 1–8 (indices 0–7), stop before item 9
    QCOMPARE(s.currentScreen(), QStringLiteral("INSTRUMENT_INTRO"));
    s.beginInstrument();
    for (int i = 0; i < 8; ++i) {
        s.setCurrentResponse(0);
        s.advance();
    }
    // Now on PHQ-9 item 9 (index 8)
    QCOMPARE(s.currentScreen(), QStringLiteral("QUESTION"));
    QCOMPARE(s.currentItemIndex(), 8);
}

void TstAppState::completeFullBattery(AppState &s)
{
    s.acknowledgeAge();
    completeInstrument(s, 1);  // ASRS

    // PHQ-9: items 1–8 with response 0, item 9 with response 0 (no crisis)
    QCOMPARE(s.currentScreen(), QStringLiteral("INSTRUMENT_INTRO"));
    s.beginInstrument();
    for (int i = 0; i < 8; ++i) {
        s.setCurrentResponse(0);
        s.advance();
    }
    // PHQ-9 item 9 = 0 (no crisis)
    s.setCurrentResponse(0);
    s.advance();

    completeInstrument(s, 1);  // GAD-7
}

// ── Age gate (FT-SAFE-03) ──────────────────────────────────────────────────

void TstAppState::welcomeScreen_initial()
{
    AppState s;
    QCOMPARE(s.currentScreen(), QStringLiteral("WELCOME"));
    QVERIFY(!s.ageAcknowledged());
}

void TstAppState::ageGate_blocksAdvance()
{
    AppState s;
    // advance() with no age acknowledgement must not leave WELCOME
    s.advance();
    QCOMPARE(s.currentScreen(), QStringLiteral("WELCOME"));
}

void TstAppState::ageGate_acknowledgeTransitions()
{
    AppState s;
    s.acknowledgeAge();
    QVERIFY(s.ageAcknowledged());
    QCOMPARE(s.currentScreen(), QStringLiteral("INSTRUMENT_INTRO"));
    QCOMPARE(s.currentInstrumentId(), QStringLiteral("ASRS"));
}

// ── Instrument sequence ───────────────────────────────────────────────────────

void TstAppState::instrumentSequence_asrsToPHQ9()
{
    AppState s;
    s.acknowledgeAge();
    completeInstrument(s, 2);
    // After ASRS completes, should be on PHQ-9 intro
    QCOMPARE(s.currentScreen(), QStringLiteral("INSTRUMENT_INTRO"));
    QCOMPARE(s.currentInstrumentId(), QStringLiteral("PHQ9"));
}

void TstAppState::instrumentSequence_phq9ToGAD7_noCrisis()
{
    AppState s;
    s.acknowledgeAge();
    completeInstrument(s, 1);  // ASRS

    // PHQ-9 with item 9 = 0
    QCOMPARE(s.currentInstrumentId(), QStringLiteral("PHQ9"));
    s.beginInstrument();
    const int count = s.sectionItemCount();
    for (int i = 0; i < count - 1; ++i) {
        s.setCurrentResponse(1);
        s.advance();
    }
    s.setCurrentResponse(0);  // item 9 = 0 (no crisis)
    s.advance();

    QCOMPARE(s.currentScreen(), QStringLiteral("INSTRUMENT_INTRO"));
    QCOMPARE(s.currentInstrumentId(), QStringLiteral("GAD7"));
    QVERIFY(!s.crisisFlag());
}

void TstAppState::instrumentSequence_gad7ToResults()
{
    AppState s;
    completeFullBattery(s);
    QCOMPARE(s.currentScreen(), QStringLiteral("RESULTS"));
    QVERIFY(s.scoresAvailable());
    QVERIFY(s.gad7Available());
}

// ── FT-SAFE-01 — PHQ-9 item 9 crisis trigger ─────────────────────────────────

void TstAppState::crisisTrigger_item9Zero_noFlag()
{
    AppState s;
    driveToPhq9Item9(s);
    s.setCurrentResponse(0);
    s.advance();
    QVERIFY(!s.crisisFlag());
    QCOMPARE(s.currentScreen(), QStringLiteral("INSTRUMENT_INTRO"));  // GAD-7 intro
}

void TstAppState::crisisTrigger_item9One_flagSet()
{
    AppState s;
    driveToPhq9Item9(s);
    s.setCurrentResponse(1);
    s.advance();
    QVERIFY(s.crisisFlag());
    QCOMPARE(s.currentScreen(), QStringLiteral("CRISIS"));
}

void TstAppState::crisisTrigger_item9Two_flagSet()
{
    AppState s;
    driveToPhq9Item9(s);
    s.setCurrentResponse(2);
    s.advance();
    QVERIFY(s.crisisFlag());
    QCOMPARE(s.currentScreen(), QStringLiteral("CRISIS"));
}

void TstAppState::crisisTrigger_item9Three_flagSet()
{
    AppState s;
    driveToPhq9Item9(s);
    s.setCurrentResponse(3);
    s.advance();
    QVERIFY(s.crisisFlag());
    QCOMPARE(s.currentScreen(), QStringLiteral("CRISIS"));
}

// ── FT-SAFE-02 — Crisis acknowledgement gate ──────────────────────────────────

void TstAppState::crisisGate_blocksResults()
{
    AppState s;
    driveToPhq9Item9(s);
    s.setCurrentResponse(1);
    s.advance();  // → CRISIS
    QCOMPARE(s.currentScreen(), QStringLiteral("CRISIS"));

    // advance() must not move past crisis without acknowledgement
    s.advance();
    QCOMPARE(s.currentScreen(), QStringLiteral("CRISIS"));

    QVERIFY(!s.scoresAvailable());
}

void TstAppState::crisisGate_acknowledgeReachesResults()
{
    AppState s;
    driveToPhq9Item9(s);
    s.setCurrentResponse(1);
    s.advance();  // → CRISIS
    s.acknowledgeCrisis();
    QCOMPARE(s.currentScreen(), QStringLiteral("RESULTS"));
    QVERIFY(s.crisisAcknowledged());
    QVERIFY(s.scoresAvailable());
}

// ── Scores ───────────────────────────────────────────────────────────────────

void TstAppState::scores_nullBeforeResults()
{
    AppState s;
    QVERIFY(!s.scoresAvailable());
    s.acknowledgeAge();
    QVERIFY(!s.scoresAvailable());
    completeInstrument(s, 1);  // ASRS done
    QVERIFY(!s.scoresAvailable());
}

void TstAppState::scores_availableAfterResults()
{
    AppState s;
    completeFullBattery(s);
    QVERIFY(s.scoresAvailable());
    // ASRS: all 6 items at 1 (Rarely) — items 1–3: 1 < 2, items 4–6: 1 < 3 → none positive
    // positiveCount = 0
    QCOMPARE(s.asrsPositiveCount(), 0);
    QVERIFY(!s.asrsPositiveScreen());
    // PHQ-9: all 9 items = 0 (completeFullBattery uses 0 to avoid crisis) → score = 0, MINIMAL
    QCOMPARE(s.phq9Score(), 0);
    QCOMPARE(s.phq9Category(), QStringLiteral("MINIMAL"));
    QVERIFY(!s.crisisFlag());
    // GAD-7: all 7 items at 1 → score = 7, MILD
    QCOMPARE(s.gad7Score(), 7);
    QCOMPARE(s.gad7Category(), QStringLiteral("MILD"));
}

void TstAppState::scores_gad7UnavailableInCrisisPath()
{
    AppState s;
    driveToPhq9Item9(s);
    s.setCurrentResponse(1);
    s.advance();       // → CRISIS
    s.acknowledgeCrisis();  // → RESULTS (GAD-7 skipped)
    QVERIFY(s.scoresAvailable());
    QVERIFY(!s.gad7Available());
}

// ── canAdvance / response ─────────────────────────────────────────────────────

void TstAppState::canAdvance_falseWithoutResponse()
{
    AppState s;
    s.acknowledgeAge();
    s.beginInstrument();
    QCOMPARE(s.currentScreen(), QStringLiteral("QUESTION"));
    QVERIFY(!s.canAdvance());
}

void TstAppState::canAdvance_trueAfterResponse()
{
    AppState s;
    s.acknowledgeAge();
    s.beginInstrument();
    s.setCurrentResponse(2);
    QVERIFY(s.canAdvance());
}

void TstAppState::canAdvance_responseChangeAllowed()
{
    AppState s;
    s.acknowledgeAge();
    s.beginInstrument();
    s.setCurrentResponse(1);
    QCOMPARE(s.currentResponse(), 1);
    s.setCurrentResponse(3);
    QCOMPARE(s.currentResponse(), 3);
    QVERIFY(s.canAdvance());
}

QTEST_MAIN(TstAppState)
#include "tst_appstate.moc"
