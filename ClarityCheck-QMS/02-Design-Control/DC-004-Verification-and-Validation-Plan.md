## DC-004 Verification & Validation Plan — ClarityCheck v1.0

**Document ID:** DC-004
**Title:** Verification & Validation Plan
**Version:** 1.0
**Date:** 2026-04-10
**Status:** Draft
**Author:** [Solo Developer / PRRC]
**Related Documents:** DC-002, DC-003, RM-003, LB-001, IEC 62304:2006+AMD1:2015

---

### 1. Purpose

This document defines the verification and validation activities for ClarityCheck v1.0 in accordance with ISO 13485 clause 7.3.6 and IEC 62304 clause 5.6–5.8. It specifies:

- The distinction between verification and validation as applied to ClarityCheck
- All planned test activities, test cases, and acceptance criteria
- Traceability from each test to the design input (DC-002), design output (DC-003), and risk control (RM-003) it verifies
- The conditions under which the device is considered verified and validated and may proceed to release

This document serves as both the plan and the results record. Test results shall be recorded in the Results columns of each test table upon execution.

---

### 2. Definitions

**Verification:** Confirmation by examination and provision of objective evidence that specified requirements have been fulfilled. *Did we build the device correctly?* — confirmed against DC-003 Design Outputs.

**Validation:** Confirmation by examination and provision of objective evidence that the particular requirements for a specific intended use can be consistently fulfilled. *Did we build the correct device?* — confirmed against DC-002 Design Inputs and the intended purpose.

These activities are distinct and both required under ISO 13485 §7.3.6 and §7.3.7.

---

### 3. Scope

This plan covers:

- Software unit verification (scoring functions)
- Instrument content verification (item text and response options)
- Functional verification (application behaviour and state transitions)
- User interface verification (screen content against DC-003 specifications)
- Safety-critical control verification (PHQ-9 item 9 crisis trigger, acknowledgement gates)
- Results document verification
- System validation (end-to-end intended use scenarios)
- Usability validation (referenced from UE-001)

This plan does not cover:

- Clinical validation of the instruments themselves (addressed in CE-002/CE-003)
- Infrastructure or browser security testing
- Performance load testing (single-user application, no server)

---

### 4. Test Environment

| Parameter | Specification |
|---|---|
| Browsers | Chrome (current), Firefox (current), Safari (current), Edge (current) |
| Mobile devices | iOS Safari (current), Android Chrome (current) |
| Minimum viewport | 320px width |
| Test data | Defined in DC-003 §4 boundary test cases |
| Unit test framework | Qt Test (QTest), executed via ctest on the desktop build kit. Tests are not run on the Wasm build target. |
| Tester | Solo Developer / PRRC |
| Test execution date | [To be completed] |

All tests shall be executed on both mobile and desktop viewport sizes unless noted otherwise.

---

### 5. Mandatory Release Criteria

The following tests are mandatory release criteria per RM-003 §5. The device shall not be released until all achieve PASS status.

| Test ID | Description | RC Reference |
|---|---|---|
| UT-ASRS-01 to UT-ASRS-10 | ASRS scoring boundary cases | RC-17, RC-18 |
| UT-PHQ-01 to UT-PHQ-12 | PHQ-9 scoring boundary cases including crisis flag | RC-17, RC-19 |
| UT-GAD-01 to UT-GAD-09 | GAD-7 scoring boundary cases | RC-17, RC-19 |
| FT-SAFE-01 | PHQ-9 item 9 crisis trigger | RC-09 |
| FT-SAFE-02 | Crisis acknowledgement gate | RC-11 |
| FT-SAFE-03 | Age acknowledgement gate | RC-26 |
| CT-01 | Character-level instrument text verification | RC-22 |

---

### 6. Unit Tests — Scoring Functions

All unit tests shall be implemented as automated tests in the chosen unit test framework. Test cases are defined in DC-003 §4 and reproduced here with results columns.

---

#### 6.1 ASRS Part A Scoring Unit Tests

**Function under test:** `ScoringEngine::scoreAsrs(const QVector<int> &responses) -> AsrsResult`
**Reference:** DC-003 §3.2, §4.1
**Risk control:** RC-17, RC-18, RC-19

| Test ID | Input [r1,r2,r3,r4,r5,r6] | Expected Score | Expected Result | Pass/Fail | Date | Tester |
|---|---|---|---|---|---|---|
| UT-ASRS-01 | [0,0,0,0,0,0] | 0 | NEGATIVE_SCREEN | | | |
| UT-ASRS-02 | [4,4,4,0,0,0] | 3 | NEGATIVE_SCREEN | | | |
| UT-ASRS-03 | [3,3,3,3,0,0] | 4 | POSITIVE_SCREEN | | | |
| UT-ASRS-04 | [4,4,4,4,4,4] | 6 | POSITIVE_SCREEN | | | |
| UT-ASRS-05 | [2,2,2,2,3,3] | 5 | POSITIVE_SCREEN | | | |
| UT-ASRS-06 | [3,0,0,0,0,4] | 2 | NEGATIVE_SCREEN | | | |
| UT-ASRS-07 | [3,3,3,0,4,0] | 4 | POSITIVE_SCREEN | | | |
| UT-ASRS-08 | [3,3,3,3,3,4] | 6 | POSITIVE_SCREEN | | | |
| UT-ASRS-09 | [2,2,2,3,0,0] | 4 | POSITIVE_SCREEN | | | |
| UT-ASRS-10 | [1,1,1,2,2,2] | 0 | NEGATIVE_SCREEN | | | |

**Key boundary notes:**
- UT-ASRS-05 verifies the group boundary: Sometimes (2) counts for items 1–3 but not item 4; Often (3) counts for items 5–6
- UT-ASRS-09 is a regression case for the corrected thresholds (negative under the superseded rule)
- UT-ASRS-10 verifies every item one step below its threshold scores 0
- UT-ASRS-06 verifies mixed threshold logic across item groups
- UT-ASRS-03 verifies exact threshold at 4 positive items

**Acceptance criterion:** All 10 tests PASS
**Result summary:** [ ] Pending re-execution — scoring thresholds corrected after the 2026-04-12 run (which passed against the superseded rule)

---

#### 6.2 PHQ-9 Scoring Unit Tests

**Function under test:** `ScoringEngine::scorePhq9(const QVector<int> &responses) -> Phq9Result`
**Reference:** DC-003 §3.3, §4.2
**Risk control:** RC-17, RC-19, RC-09

| Test ID | Input [r1..r9] | Exp. Score | Exp. Category | Exp. Crisis Flag | Pass/Fail | Date | Tester |
|---|---|---|---|---|---|---|---|
| UT-PHQ-01 | [0,0,0,0,0,0,0,0,0] | 0 | MINIMAL | FALSE | PASS | 2026-04-12 | PRRC |
| UT-PHQ-02 | [1,1,1,0,0,0,0,0,0] | 3 | MINIMAL | FALSE | PASS | 2026-04-12 | PRRC |
| UT-PHQ-03 | [1,1,1,1,0,0,0,0,0] | 4 | MINIMAL | FALSE | PASS | 2026-04-12 | PRRC |
| UT-PHQ-04 | [1,1,1,1,1,0,0,0,0] | 5 | MILD | FALSE | PASS | 2026-04-12 | PRRC |
| UT-PHQ-05 | [1,1,1,1,1,1,1,1,1] | 9 | MILD | TRUE | PASS | 2026-04-12 | PRRC |
| UT-PHQ-06 | [2,2,1,1,1,1,1,1,0] | 10 | MODERATE | FALSE | PASS | 2026-04-12 | PRRC |
| UT-PHQ-07 | [2,2,2,2,2,2,1,1,0] | 14 | MODERATE | FALSE | PASS | 2026-04-12 | PRRC |
| UT-PHQ-08 | [2,2,2,2,2,2,2,1,0] | 15 | MODERATELY_SEVERE | FALSE | PASS | 2026-04-12 | PRRC |
| UT-PHQ-09 | [2,2,2,2,2,2,2,2,3] | 19 | MODERATELY_SEVERE | TRUE | PASS | 2026-04-12 | PRRC |
| UT-PHQ-10 | [3,3,2,2,2,2,2,2,2] | 20 | SEVERE | TRUE | PASS | 2026-04-12 | PRRC |
| UT-PHQ-11 | [3,3,3,3,3,3,3,3,3] | 27 | SEVERE | TRUE | PASS | 2026-04-12 | PRRC |
| UT-PHQ-12 | [0,0,0,0,0,0,0,0,1] | 1 | MINIMAL | TRUE | PASS | 2026-04-12 | PRRC |

**Key boundary notes:**
- UT-PHQ-03/04 verify 4/5 boundary (MINIMAL/MILD threshold)
- UT-PHQ-07/08 verify 14/15 boundary (MODERATE/MODERATELY_SEVERE threshold)
- UT-PHQ-09/10 verify 19/20 boundary (MODERATELY_SEVERE/SEVERE threshold)
- UT-PHQ-05 verifies crisis flag triggered at item 9 = 1 within MILD range
- UT-PHQ-12 verifies crisis flag triggered by item 9 alone regardless of total score

**Acceptance criterion:** All 12 tests PASS
**Result summary:** [x] All pass — Qt Test 6.8.3, 2026-04-12, Windows 11 x86_64, GCC 13.1.0

---

#### 6.3 GAD-7 Scoring Unit Tests

**Function under test:** `ScoringEngine::scoreGad7(const QVector<int> &responses) -> Gad7Result`
**Reference:** DC-003 §3.4, §4.3
**Risk control:** RC-17, RC-19

| Test ID | Input [r1..r7] | Exp. Score | Exp. Category | Pass/Fail | Date | Tester |
|---|---|---|---|---|---|---|
| UT-GAD-01 | [0,0,0,0,0,0,0] | 0 | MINIMAL | PASS | 2026-04-12 | PRRC |
| UT-GAD-02 | [1,1,1,1,0,0,0] | 4 | MINIMAL | PASS | 2026-04-12 | PRRC |
| UT-GAD-03 | [1,1,1,1,1,0,0] | 5 | MILD | PASS | 2026-04-12 | PRRC |
| UT-GAD-04 | [1,1,1,1,1,1,1] | 7 | MILD | PASS | 2026-04-12 | PRRC |
| UT-GAD-05 | [2,2,1,1,1,1,1] | 9 | MILD | PASS | 2026-04-12 | PRRC |
| UT-GAD-06 | [2,2,2,1,1,1,1] | 10 | MODERATE | PASS | 2026-04-12 | PRRC |
| UT-GAD-07 | [2,2,2,2,2,2,2] | 14 | MODERATE | PASS | 2026-04-12 | PRRC |
| UT-GAD-08 | [3,2,2,2,2,2,2] | 15 | SEVERE | PASS | 2026-04-12 | PRRC |
| UT-GAD-09 | [3,3,3,3,3,3,3] | 21 | SEVERE | PASS | 2026-04-12 | PRRC |

**Key boundary notes:**
- UT-GAD-02/03 verify 4/5 boundary (MINIMAL/MILD)
- UT-GAD-05/06 verify 9/10 boundary (MILD/MODERATE)
- UT-GAD-07/08 verify 14/15 boundary (MODERATE/SEVERE)

**Acceptance criterion:** All 9 tests PASS
**Result summary:** [x] All pass — Qt Test 6.8.3, 2026-04-12, Windows 11 x86_64, GCC 13.1.0

---

### 7. Content Verification Tests — Instrument Text

**Reference:** DC-003 §2, §6
**Risk control:** RC-21, RC-22

---

#### CT-01 — ASRS Part A Item Text Verification

**Method:** Extract all ASRS item text strings from deployed application. Compare character by character against DC-003 §2.1 reference table.

| Item | DC-003 Reference Text (first 8 words) | Deployed Text Matches | Pass/Fail | Date |
|---|---|---|---|---|
| 1 | "How often do you have trouble wrapping..." | | | |
| 2 | "How often do you have difficulty getting..." | | | |
| 3 | "How often do you have problems remembering..." | | | |
| 4 | "When you have a task that requires..." | | | |
| 5 | "How often do you fidget or squirm..." | | | |
| 6 | "How often do you feel overly active..." | | | |
| Response options | Never / Rarely / Sometimes / Often / Very Often | | | |

**Acceptance criterion:** All 6 items and response options match DC-003 §2.1 exactly — zero deviations
**Full text comparison:** Attach character-level comparison output as CT-01-Evidence

---

#### CT-02 — PHQ-9 Item Text Verification

**Method:** As CT-01 against DC-003 §2.2 reference table.

| Item | Verified Against DC-003 §2.2 | Pass/Fail | Date |
|---|---|---|---|
| 1 | Little interest or pleasure in doing things | | |
| 2 | Feeling down, depressed, or hopeless | | |
| 3 | Trouble falling or staying asleep, or sleeping too much | | |
| 4 | Feeling tired or having little energy | | |
| 5 | Poor appetite or overeating | | |
| 6 | Feeling bad about yourself... | | |
| 7 | Trouble concentrating on things... | | |
| 8 | Moving or speaking so slowly... | | |
| 9 | Thoughts that you would be better off dead... | | |
| Response options | Not at all / Several days / More than half the days / Nearly every day | | |
| Functional item | Omitted from research version — pending OIR-08 resolution | N/A | N/A |

**Acceptance criterion:** All 9 scored items and response options match DC-003 §2.2 exactly. Functional item omitted per OIR-08.
**Full text comparison:** Attach as CT-02-Evidence

---

#### CT-03 — GAD-7 Item Text Verification

**Method:** As CT-01 against DC-003 §2.3 reference table.

| Item | Verified Against DC-003 §2.3 | Pass/Fail | Date |
|---|---|---|---|
| 1 | Feeling nervous, anxious, or on edge | | |
| 2 | Not being able to stop or control worrying | | |
| 3 | Worrying too much about different things | | |
| 4 | Trouble relaxing | | |
| 5 | Being so restless that it is hard to sit still | | |
| 6 | Becoming easily annoyed or irritable | | |
| 7 | Feeling afraid as if something awful might happen | | |
| Response options | Not at all / Several days / More than half the days / Nearly every day | | |
| Functional item | Omitted from research version — pending OIR-08 resolution | N/A | N/A |

**Acceptance criterion:** All 7 scored items and response options match DC-003 §2.3 exactly. Functional item omitted per OIR-08.
**Full text comparison:** Attach as CT-03-Evidence

---

#### CT-04 — Prohibited Term Audit

**Method:** Automated text search of all user-facing string resources for prohibited terms defined in DC-003 §6. Manual review of any matches to confirm permitted/non-permitted context.

| Term | Occurrences Found | Permitted Occurrences | Non-Permitted Occurrences | Pass/Fail | Date |
|---|---|---|---|---|---|
| diagnosis | | | | | |
| diagnose | | | | | |
| diagnosed | | | | | |
| diagnostic | | | | | |
| you have ADHD | | | | | |
| you have depression | | | | | |
| you have anxiety | | | | | |
| confirms | | | | | |
| proves | | | | | |
| clinical report | | | | | |
| assessment report | | | | | |

**Acceptance criterion:** Zero non-permitted occurrences of any prohibited term
**Result:** [ ] Pass [ ] Fail — list non-permitted occurrences:

---

### 8. Functional Tests — Application Behaviour

---

#### FT-FLOW-01 — Assessment Sequence Enforcement

**Requirement:** FR-01
**Reference:** DC-003 §7 state model
**Description:** Verify that instruments are presented in the correct fixed sequence: ASRS Part A → PHQ-9 → GAD-7.

| Step | Action | Expected Result | Pass/Fail | Date |
|---|---|---|---|---|
| 1 | Complete age gate and begin assessment | ASRS introduction screen displayed | | |
| 2 | Complete all 6 ASRS items | PHQ-9 introduction screen displayed | | |
| 3 | Complete all 9 PHQ-9 items (item 9 = 0) | GAD-7 introduction screen displayed | | |
| 4 | Complete all 7 GAD-7 items | Results screen displayed | | |

**Acceptance criterion:** All steps pass on mobile and desktop

---

#### FT-FLOW-02 — Item Skip Prevention

**Requirement:** FR-03
**Description:** Verify that the Next button is disabled until a response is selected, preventing item skipping.

| Step | Action | Expected Result | Pass/Fail | Date |
|---|---|---|---|---|
| 1 | Load any question screen with no response selected | Next button disabled / inactive | | |
| 2 | Select a response option | Next button enabled | | |
| 3 | Attempt to advance without selecting (keyboard/direct navigation) | Advance blocked | | |

**Acceptance criterion:** All steps pass; no question can be bypassed without a response

---

#### FT-FLOW-03 — Response Change Permitted

**Requirement:** FR-04
**Description:** Verify that a user can change their response before advancing.

| Step | Action | Expected Result | Pass/Fail | Date |
|---|---|---|---|---|
| 1 | Select response option A on any item | Option A shown as selected | | |
| 2 | Select response option B on the same item | Option B shown as selected; option A deselected | | |
| 3 | Advance to next item | Option B recorded in application state | | |

**Acceptance criterion:** All steps pass

---

#### FT-FLOW-04 — Progress Indicator

**Requirement:** FR-06, DC-003 §5.3
**Description:** Verify that a progress indicator is displayed throughout the assessment.

| Step | Action | Expected Result | Pass/Fail | Date |
|---|---|---|---|---|
| 1 | Load first ASRS question | Progress indicator displays (e.g. Question 1 of 22) | | |
| 2 | Advance through assessment | Progress indicator updates on each item | | |
| 3 | Load first PHQ-9 question | Progress indicator shows item 7 of 22 | | |
| 4 | Load first GAD-7 question | Progress indicator shows item 16 of 22 | | |
| 5 | Load last GAD-7 question | Progress indicator shows item 22 of 22 | | |

**Acceptance criterion:** Progress indicator present and accurate on all 22 question screens

---

#### FT-SAFE-01 — PHQ-9 Item 9 Crisis Trigger ⚠️ MANDATORY

**Requirement:** FR-19, RC-09
**Reference:** DC-003 §5.4, §7
**Description:** Verify that any non-zero response to PHQ-9 item 9 triggers the crisis screen before results are displayed. Verify that a zero response does not trigger it.

| Test | Item 9 Response | Expected Behaviour | Pass/Fail | Date |
|---|---|---|---|---|
| FT-SAFE-01a | 0 (Not at all) | No crisis screen; results displayed directly | PASS | 2026-04-12 |
| FT-SAFE-01b | 1 (Several days) | Crisis screen displayed before results | PASS | 2026-04-12 |
| FT-SAFE-01c | 2 (More than half the days) | Crisis screen displayed before results | PASS | 2026-04-12 |
| FT-SAFE-01d | 3 (Nearly every day) | Crisis screen displayed before results | PASS | 2026-04-12 |

**Verification method:** Automated unit tests in tst_appstate (crisisTrigger_* test cases), Qt Test 6.8.3, 2026-04-12, Windows 11 x86_64.

**Additional checks:**
- [ ] Crisis screen content matches DC-003 §5.4 specification — *pending UI implementation (Phase 4)*
- [x] Results screen is not accessible until crisis screen is displayed and acknowledged — verified by tst_appstate::crisisGate_blocksResults
- [x] Crisis screen displayed regardless of total PHQ-9 score — verified by tst_appstate::crisisTrigger_item9One_flagSet (score 1, MINIMAL)

**Acceptance criterion:** 4/4 subtests pass; all additional checks confirmed. ZERO tolerance for failure.
**Result:** [x] State machine logic: all pass. UI content check pending Phase 4.

---

#### FT-SAFE-02 — Crisis Acknowledgement Gate ⚠️ MANDATORY

**Requirement:** FR-21, RC-11
**Reference:** DC-003 §5.4
**Description:** Verify that the results screen is inaccessible until the crisis screen acknowledgement button is activated.

| Step | Action | Expected Result | Pass/Fail | Date |
|---|---|---|---|---|
| 1 | Trigger crisis screen (item 9 > 0) | Crisis screen displayed; results not visible | PASS | 2026-04-12 |
| 2 | Attempt to navigate to results without activating button | Navigation blocked | PASS | 2026-04-12 |
| 3 | Activate acknowledgement button | Results screen displayed | PASS | 2026-04-12 |
| 4 | Verify acknowledgement button text | *"I have read the above. Continue to my results."* | Pending UI | — |

**Verification method (steps 1–3):** Automated unit tests in tst_appstate (crisisGate_blocksResults, crisisGate_acknowledgeReachesResults), Qt Test 6.8.3, 2026-04-12. Step 4 requires UI implementation (Phase 4).

**Acceptance criterion:** All steps pass; results screen unreachable without acknowledgement. ZERO tolerance for failure.

---

#### FT-SAFE-03 — Age Acknowledgement Gate ⚠️ MANDATORY

**Requirement:** RC-26, DC-003 §5.1
**Description:** Verify that the assessment cannot begin until the age acknowledgement gate is activated.

| Step | Action | Expected Result | Pass/Fail | Date |
|---|---|---|---|---|
| 1 | Load welcome screen | Age gate displayed; Begin button disabled | Pending UI | — |
| 2 | Attempt to begin without activating gate | Begin button remains inactive | PASS | 2026-04-12 |
| 3 | Activate age acknowledgement | Begin button enabled | PASS | 2026-04-12 |
| 4 | Activate Begin button | ASRS introduction screen displayed | PASS | 2026-04-12 |

**Verification method (steps 2–4):** Automated unit tests in tst_appstate (ageGate_blocksAdvance, ageGate_acknowledgeTransitions), Qt Test 6.8.3, 2026-04-12. Step 1 (Begin button visual state) requires UI implementation (Phase 3).

**Acceptance criterion:** All steps pass; assessment unreachable without age acknowledgement. ZERO tolerance for failure.

---

#### FT-SAFE-04 — Persistent Crisis Resource Link

**Requirement:** RC-28, DC-003 §5.3
**Description:** Verify that a crisis resource link is present and functional on all 22 question screens.

| Check | Screen | Crisis Link Present | Crisis Link Functional | Pass/Fail | Date |
|---|---|---|---|---|---|
| 1 | ASRS item 1 | | | | |
| 2 | ASRS item 6 (last) | | | | |
| 3 | PHQ-9 item 1 | | | | |
| 4 | PHQ-9 item 9 | | | | |
| 5 | GAD-7 item 1 | | | | |
| 6 | GAD-7 item 7 (last) | | | | |

**Acceptance criterion:** Crisis link present and navigates to crisis resources screen on all checked screens; spot check 6 of 22 screens is minimum acceptable for v1.0

---

#### FT-DATA-01 — No Persistent Data Storage

**Requirement:** NFR-07, NFR-08, NFR-09
**Reference:** DC-003 §8
**Description:** Verify that no response data is written to any persistent browser storage mechanism.

| Step | Action | Expected Result | Pass/Fail | Date |
|---|---|---|---|---|
| 1 | Complete full assessment | Results displayed | | |
| 2 | Inspect localStorage | Empty — no ClarityCheck keys | | |
| 3 | Inspect sessionStorage | Empty — no ClarityCheck keys | | |
| 4 | Inspect IndexedDB | No ClarityCheck database | | |
| 5 | Inspect network requests during assessment | Zero outbound requests containing response data | | |
| 6 | Close tab and reopen app | No pre-populated responses; fresh session | | |

**Acceptance criterion:** All steps pass; zero data persistence beyond active session

---

### 9. User Interface Verification Tests

---

#### UI-01 — Welcome Screen Content

**Reference:** DC-003 §5.1
**Description:** Verify all required elements are present on the welcome screen.

| Element | Required Content | Present | Correct | Pass/Fail | Date |
|---|---|---|---|---|---|
| App name | ClarityCheck | | | | |
| App version | 1.0 | | | | |
| Purpose statement | Screening tool, not diagnostic | | | | |
| Crisis advisory | Per LB-001 §1 | | | | |
| Crisis resource link | Present and functional | | | | |
| Emotional content advisory | Per RC-27 | | | | |
| Age restriction statement | 18 and over | | | | |
| Age acknowledgement gate | Checkbox present | | | | |
| Screening disclaimer | Not a diagnostic tool | | | | |
| Begin button | Disabled until gate activated | | | | |
| IFU link | Present and functional | | | | |

**Acceptance criterion:** All 11 elements present and correct on mobile and desktop

---

#### UI-02 — Results Screen Content

**Reference:** DC-003 §5.5
**Description:** Verify all required elements are present on the results screen.

| Element | Required | Present | Correct | Pass/Fail | Date |
|---|---|---|---|---|---|
| Global screening disclaimer | Top of screen, prominent | | | | |
| ASRS results card — score | Numeric | | | | |
| ASRS results card — result | Positive/Negative | | | | |
| ASRS results card — interpretation | Per LB-001 §7 | | | | |
| ASRS negative sensitivity statement | Per RC-02 | | | | |
| ASRS self-medication warning (if positive) | Per RC-32 | | | | |
| PHQ-9 results card — score | Numeric 0–27 | | | | |
| PHQ-9 results card — category | Severity label | | | | |
| PHQ-9 results card — interpretation | Per LB-001 §7 | | | | |
| PHQ-9 limitation disclaimer | Per RC-06 | | | | |
| GAD-7 results card — score | Numeric 0–21 | | | | |
| GAD-7 results card — category | Severity label | | | | |
| GAD-7 results card — interpretation | Per LB-001 §7 | | | | |
| GAD-7 limitation disclaimer | Per RC-08 | | | | |
| Per-card disclaimer | On each card | | | | |
| Clinical referral advisory | Share with doctor | | | | |
| Save/print button | Present and functional | | | | |
| IFU link | Present and functional | | | | |
| Crisis resource link | Present and functional | | | | |

**Acceptance criterion:** All elements present and correct on mobile and desktop

---

#### UI-03 — Results Screen: ASRS Self-Medication Warning Conditional Display

**Reference:** DC-003 §5.5, RC-32
**Description:** Verify that the self-medication warning is displayed when ASRS result is POSITIVE_SCREEN and not displayed when NEGATIVE_SCREEN.

| Test | ASRS Result | Self-Medication Warning Displayed | Pass/Fail | Date |
|---|---|---|---|---|
| UI-03a | POSITIVE_SCREEN | Yes | | |
| UI-03b | NEGATIVE_SCREEN | No | | |

**Acceptance criterion:** Both subtests pass

---

#### UI-04 — Results Document Content

**Reference:** DC-003 §5.6, RC-29, RC-30, RC-31
**Description:** Generate a sample results document and verify required elements.

| Element | Required | Present | Correct | Pass/Fail | Date |
|---|---|---|---|---|---|
| Document title | *"ClarityCheck Screening Results"* | | | | |
| Disclaimer header | Per RC-29 — top of document | | | | |
| Date of completion | Auto-populated | | | | |
| App version | 1.0 | | | | |
| ASRS score and result | Correct | | | | |
| PHQ-9 score and category | Correct | | | | |
| GAD-7 score and category | Correct | | | | |
| Per-section disclaimers | On each section | | | | |
| Sharing advisory | Per LB-001 §9 | | | | |
| ASRS copyright notice | Per DC-003 §9 | | | | |
| PHQ-9 copyright notice | Per DC-003 §9 | | | | |
| GAD-7 copyright notice | Per DC-003 §9 | | | | |
| Footer | Version, license, manufacturer | | | | |
| No clinical formatting | No letterhead, no MRN field | | | | |

**Acceptance criterion:** All elements present and correct; document does not resemble a clinical record

---

#### UI-05 — Copyright Notices

**Reference:** DC-003 §9
**Description:** Verify copyright notices are present in all required locations.

| Notice | Location | Present | Verbatim | Pass/Fail | Date |
|---|---|---|---|---|---|
| ASRS © NYU/Harvard | ASRS intro screen | | | | |
| ASRS © NYU/Harvard | Results document | | | | |
| ASRS © NYU/Harvard | IFU §4 | | | | |
| PHQ-9 © Pfizer | PHQ-9 intro screen | | | | |
| PHQ-9 © Pfizer | Results document | | | | |
| PHQ-9 © Pfizer | IFU §4 | | | | |
| GAD-7 © Pfizer | GAD-7 intro screen | | | | |
| GAD-7 © Pfizer | Results document | | | | |
| GAD-7 © Pfizer | IFU §4 | | | | |

**Acceptance criterion:** All 9 copyright notice instances present and verbatim per DC-003 §9

---

#### UI-06 — Viewport Compatibility

**Reference:** DC-002 NFR-03, NFR-04
**Description:** Verify application is functional and legible at minimum supported viewport width.

| Check | Viewport | Result | Pass/Fail | Date |
|---|---|---|---|---|
| Welcome screen legible | 320px | | | |
| Question screens legible | 320px | | | |
| Response options tappable | Mobile touch | | | |
| Results screen legible | 320px | | | |
| Progress indicator visible | 320px | | | |
| Crisis screen legible | 320px | | | |
| Results disclaimer visible without scrolling | 320px | | | |

**Acceptance criterion:** All checks pass at 320px width and on mobile touch input

---

#### UI-07 — Browser Compatibility

**Reference:** DC-002 NFR-10, NFR-11
**Description:** Execute core functional test suite across all supported browsers.

| Browser | FT-SAFE-01 | FT-SAFE-02 | FT-SAFE-03 | UT scoring | Overall | Date |
|---|---|---|---|---|---|---|
| Chrome (desktop, current) | | | | | | |
| Firefox (desktop, current) | | | | | | |
| Safari (desktop, current) | | | | | | |
| Edge (desktop, current) | | | | | | |
| Chrome (Android, current) | | | | | | |
| Safari (iOS, current) | | | | | | |

**Acceptance criterion:** All safety-critical and scoring tests pass on all 6 browser/platform combinations

---

### 10. Validation — End-to-End Scenarios

Validation confirms the device meets the intended purpose from DC-002 §2. These are scenario-based tests representing real intended use.

---

#### VAL-01 — Standard Completion: Negative Screen, Low Comorbidity

**Scenario:** Adult user with no significant symptoms completes the full battery.
**Inputs:** ASRS responses all low (positive count 0–1); PHQ-9 total ≤ 4; GAD-7 total ≤ 4; PHQ-9 item 9 = 0

| Step | Expected Outcome | Pass/Fail | Date |
|---|---|---|---|
| Welcome screen loads | Crisis advisory, age gate, screening disclaimer visible | | |
| User confirms age and begins | ASRS intro displayed | | |
| ASRS completed | PHQ-9 intro displayed | | |
| PHQ-9 completed (item 9 = 0) | GAD-7 intro displayed (no crisis screen) | | |
| GAD-7 completed | Results screen displayed | | |
| Results screen | ASRS negative, PHQ-9 minimal, GAD-7 minimal shown with correct categories | | |
| ASRS negative sensitivity statement | Present on results screen | | |
| No self-medication warning | Correct — ASRS negative | | |
| User saves results | Results document generated with disclaimer header | | |

**Acceptance criterion:** All steps pass; output consistent with intended purpose

---

#### VAL-02 — Standard Completion: Positive Screen, Moderate Comorbidity

**Scenario:** Adult user with significant symptoms completes the full battery.
**Inputs:** ASRS positive count ≥ 4; PHQ-9 total 10–14; GAD-7 total 10–14; PHQ-9 item 9 = 0

| Step | Expected Outcome | Pass/Fail | Date |
|---|---|---|---|
| ASRS completed | Positive screen result | | |
| PHQ-9 completed (item 9 = 0) | GAD-7 intro displayed (no crisis screen) | | |
| Results screen | ASRS positive, PHQ-9 moderate, GAD-7 moderate shown correctly | | |
| ASRS self-medication warning | Present — ASRS positive | | |
| Clinical referral advisory | Prominent on results screen | | |
| PHQ-9 and GAD-7 limitation disclaimers | Present on respective cards | | |
| User saves results | Document includes all scores and disclaimer header | | |

**Acceptance criterion:** All steps pass; positive result handling correct throughout

---

#### VAL-03 — Crisis Pathway: PHQ-9 Item 9 Non-Zero

**Scenario:** Adult user endorses suicidal ideation item during PHQ-9.
**Inputs:** PHQ-9 item 9 = 1; all other responses minimal

| Step | Expected Outcome | Pass/Fail | Date |
|---|---|---|---|
| PHQ-9 item 9 response = 1 selected | Response recorded | | |
| PHQ-9 final item advanced | Crisis screen displayed immediately | | |
| Crisis screen content | Helpline references present; acknowledgement button present | | |
| Results screen inaccessible | Cannot be reached without acknowledgement | | |
| Acknowledgement button activated | Results screen displayed | | |
| PHQ-9 score on results | Correctly calculated including item 9 value | | |
| Crisis resource link | Present on results screen | | |

**Acceptance criterion:** All steps pass; crisis pathway functions correctly end to end; ZERO tolerance for failure

---

#### VAL-04 — Intended Purpose Validation: Output Supports Clinical Consultation Preparation

**Scenario:** Evaluate whether the output of ClarityCheck v1.0 is suitable to support a user in preparing for a clinical consultation, as stated in the intended purpose.

**Method:** Structured review by clinical reviewer (per CE-001 §11 — clinician reviewer to be engaged)

| Criterion | Reviewer Assessment | Pass/Fail | Date |
|---|---|---|---|
| Results contain sufficient information to initiate an ADHD-focused GP consultation | | | |
| Results language is appropriate for a lay user to understand | | | |
| Disclaimers adequately communicate screening-only nature of output | | | |
| Referral advisory is actionable and clear | | | |
| Clinician receiving results document would understand its context and limitations | | | |

**Acceptance criterion:** Clinical reviewer confirms all 5 criteria met
**Reviewer name and qualifications:** [To be completed — linked to CE-001 OI-01]

---

#### VAL-05 — IFU Readability

**Requirement:** NFR-05
**Description:** Verify IFU LB-001 achieves Flesch-Kincaid Grade 8 or below.

| Section | FK Grade Score | Pass/Fail | Date |
|---|---|---|---|
| LB-001 §1 (Important) | | | |
| LB-001 §2 (Who is it for) | | | |
| LB-001 §7 (Understanding results) | | | |
| LB-001 §8 (Limitations) | | | |
| LB-001 overall | | | |

**Method:** FK grade analysis using [tool to be specified — e.g. Hemingway App, MS Word readability stats]
**Acceptance criterion:** Overall FK Grade ≤ 8; no individual section exceeds Grade 10

---

### 11. Traceability Matrix

| DC-002 Requirement | DC-003 Output | RM-003 RC | DC-004 Test | Pass/Fail |
|---|---|---|---|---|
| FR-01 Sequence | §5 screen specs | — | FT-FLOW-01 | |
| FR-02 All items | §2 instrument spec | RC-21 | CT-01/02/03 | |
| FR-03 No skip | §5.3 question screen | — | FT-FLOW-02 | |
| FR-04 Change answer | §5.3 question screen | — | FT-FLOW-03 | |
| FR-06 Progress | §5.3 question screen | — | FT-FLOW-04 | |
| FR-07 ASRS scoring | §3.2 scoring spec | RC-17, RC-18 | UT-ASRS-01–10 | |
| FR-08 PHQ-9 scoring | §3.3 scoring spec | RC-17 | UT-PHQ-01–12 | |
| FR-09 GAD-7 scoring | §3.4 scoring spec | RC-17 | UT-GAD-01–09 | |
| FR-10 Thresholds | §3 scoring spec | RC-17 | UT-PHQ/GAD boundaries | |
| FR-11 Client-side | §8 data handling | — | FT-DATA-01 | |
| FR-12 Results screen | §5.5 results spec | — | UI-02 | |
| FR-13 Per-instrument scores | §5.5 results spec | RC-06, RC-08 | UI-02 | |
| FR-14 Plain-language | §5.5 results spec | RC-04, RC-05 | UI-02 | |
| FR-15 Not-a-diagnosis | §5.5, §6 | RC-14, RC-16 | UI-02, CT-04 | |
| FR-16 Clinical referral | §5.5 results spec | — | UI-02 | |
| FR-17 Print/save | §5.6 document spec | RC-29, RC-31 | UI-04 | |
| FR-18 No storage | §8 data handling | — | FT-DATA-01 | |
| FR-19 Crisis trigger | §5.4, §7 state | RC-09 | FT-SAFE-01 | |
| FR-20 Crisis content | §5.4 crisis screen | RC-10 | FT-SAFE-01 | |
| FR-21 Crisis gate | §5.4, §7 state | RC-11 | FT-SAFE-02 | |
| FR-22 Intended purpose | §5.1 welcome | RC-03 | UI-01 | |
| FR-23 Copyright | §9 notices | RC-21 | UI-05 | |
| FR-24 Version | §10 labeling | — | UI-01, UI-04 | |
| FR-25 IFU access | §5.1, §5.5 | — | UI-01, UI-02 | |
| FR-26 Not diagnostic | §5.1, §6 | RC-03, RC-16 | UI-01, CT-04 | |
| NFR-03 320px legible | §5 screen specs | — | UI-06 | |
| NFR-04 Touch targets | §5 screen specs | — | UI-06 | |
| NFR-05 FK Grade 8 | LB-001 | — | VAL-05 | |
| NFR-06 No login | §8 data handling | — | FT-DATA-01 | |
| NFR-07 No PII | §8 data handling | — | FT-DATA-01 | |
| NFR-08 No transmission | §8 data handling | — | FT-DATA-01 | |
| NFR-09 Session cleared | §8 data handling | — | FT-DATA-01 | |
| NFR-10/11 Browser compat | §4 test environment | — | UI-07 | |
| RC-09 | §5.4 crisis screen | RC-09 | FT-SAFE-01 | |
| RC-11 | §5.4 crisis gate | RC-11 | FT-SAFE-02 | |
| RC-26 | §5.1 age gate | RC-26 | FT-SAFE-03 | |

---

### 12. Defect Classification and Release Criteria

#### 12.1 Defect Classification

| Class | Definition | Release Impact |
|---|---|---|
| Critical | Safety-critical control failure (FT-SAFE-01, FT-SAFE-02, FT-SAFE-03); scoring error; prohibited term in results | Blocks release — must be resolved and retested |
| Major | Incorrect score category at boundary; missing disclaimer; copyright notice absent; incorrect item text | Blocks release — must be resolved and retested |
| Minor | UI layout issue; non-critical text error; cosmetic defect | Does not block release — log and schedule for patch |

#### 12.2 Release Sign-Off Criteria

All of the following must be satisfied before v1.0 release:

- [ ] All mandatory release tests passed (§5)
- [ ] Zero Critical defects open
- [ ] Zero Major defects open
- [ ] All unit tests passing in automated suite
- [ ] VAL-04 clinical reviewer sign-off obtained
- [ ] VAL-05 IFU readability confirmed ≤ Grade 8
- [ ] CT-01, CT-02, CT-03 character-level evidence attached
- [ ] FT-DATA-01 network inspection evidence attached
- [ ] All tests executed on minimum 4 desktop browsers and 2 mobile browsers
- [ ] PRRC sign-off below

---

### 13. Test Execution Record

| Test Suite | Total Tests | Passed | Failed | Not Run | Date | Tester |
|---|---|---|---|---|---|---|
| Unit — ASRS | 8 | | | | | |
| Unit — PHQ-9 | 12 | | | | | |
| Unit — GAD-7 | 9 | | | | | |
| Content — Text | 4 | | | | | |
| Functional — Flow | 4 | | | | | |
| Functional — Safety | 4 | | | | | |
| Functional — Data | 1 | | | | | |
| UI Verification | 7 | | | | | |
| Validation | 5 | | | | | |
| **Total** | **54** | | | | | |

---

### 14. Review and Approval

| Role | Name | Date | Signature |
|---|---|---|---|
| Author / PRRC | | | |
| Clinical Reviewer (VAL-04) | | | |

---

### 15. Open Items

| ID | Item | Owner | Due |
|---|---|---|---|
| OI-01 | Select and configure unit test framework | PRRC | Before development |
| OI-02 | Confirm FK grade analysis tool (VAL-05) | PRRC | Before IFU finalisation |
| OI-03 | Engage clinical reviewer for VAL-04 (linked to CE-001 OI-01) | PRRC | Before release |
| OI-04 | Confirm crisis helpline references for FT-SAFE-01 content check | PRRC | Linked to RM-002 OI-01 |
| OI-05 | Execute all tests post-implementation and record results | PRRC | Release milestone |

---

DC-004 is now complete. The QMS document set is substantially finished.

---

## QMS Status Overview — ClarityCheck v1.0

| Document | Status |
|---|---|
| DDR-001 Sleep domain exclusion | ✅ Complete |
| DDR-002 ASRS Part A only | ✅ Complete |
| RG-001 Annex A IP Clearance | ✅ Complete |
| DC-002 Design Inputs | ✅ Complete |
| DC-003 Design Outputs | ✅ Complete |
| DC-004 Verification & Validation Plan | ✅ Complete |
| RM-001 Risk Management Plan | ✅ Complete |
| RM-002 Risk Assessment FMEA | ✅ Complete |
| RM-003 Risk Control Measures | ✅ Complete |
| LB-001 Instructions for Use | ✅ Complete |
| RM-004 Residual Risk Evaluation | ✅ Complete (Draft) |
| CE-001 Clinical Evaluation Plan | ✅ Complete |
| CE-002 Literature Review | ✅ Complete (Draft) |
| CE-003 Clinical Evaluation Report | ✅ Complete (Draft — Pending Clinical Reviewer Sign-Off) |
| UE-001 Usability Engineering Plan | ✅ Complete (Draft) |
| QM-001 Quality Manual | ✅ Complete (Draft) |

All planned QMS documents are now drafted. Remaining open items before release:

- **Clinical Reviewer sign-off** — required for CE-001, CE-002, CE-003, LB-001
- **Test execution** — V&V tests in this document must be run and results recorded
- **Manufacturer identity** — legal entity details in QM-001
- **RG-002** Declaration of Conformity — pre-release deliverable
- **FE-001, UE-003, UE-004** — usability evaluation reports (at defined lifecycle stages)