## UE-001 Usability Engineering Plan — ClarityCheck v1.0

**Document ID:** UE-001
**Title:** Usability Engineering Plan
**Version:** 1.0
**Date:** 2026-04-10
**Status:** Draft
**Author:** [Solo Developer / PRRC]
**Related Documents:** DC-002, DC-003, RM-001, RM-002, LB-001, IEC 62366-1:2015

---

### 1. Purpose

This document defines the usability engineering process for ClarityCheck v1.0 in accordance with IEC 62366-1:2015. It describes the planned activities to identify, analyse, specify, verify, and validate usability characteristics of the device with respect to safety and effectiveness of use.

The goal of usability engineering in the context of ClarityCheck is not aesthetic — it is safety-driven. The primary usability concern is that a lay user in a potentially vulnerable emotional state can complete the assessment accurately, understand their results without misinterpretation, and be directed to appropriate support when needed.

---

### 2. Scope

This plan covers:

- Intended use specification from a usability perspective
- User profile and use environment analysis
- Identification of use-related hazards and critical tasks
- Formative evaluation activities (during design)
- Summative usability testing (before release)
- Traceability to risk controls and design outputs

This plan does not cover:

- Clinical validation of instruments (CE-001/CE-002)
- Software unit verification (DC-004)
- Post-market usability feedback (PM-001)

---

### 3. Regulatory and Standards Basis

| Standard / Guidance | Application |
|---|---|
| IEC 62366-1:2015 | Primary usability engineering standard |
| IEC 62366-1:2015 AMD1:2020 | Amendment — clarifications on summative evaluation |
| MDR 2017/745 Annex I §5 | General safety and performance requirements for usability |
| FDA Guidance: Applying Human Factors (2016) | Reference for use-related risk analysis methodology |

---

### 4. Intended Use — Usability Perspective

Restating DC-002 §2 from a usability lens:

**Task:** A lay adult completes a 22-item self-administered questionnaire battery on a personal device, receives scored results, and optionally saves or prints the results to share with a clinician.

**Critical outcome:** The user understands that results are screening outputs, not diagnoses, and takes the appropriate action (seek clinical consultation if indicated; seek crisis support if PHQ-9 item 9 is positive).

**Failure modes of concern:**
- User misinterprets a positive screen as a diagnosis
- User misinterprets a negative screen as a rule-out
- User in crisis is not directed to support
- User under 18 completes an instrument validated for adults only
- User enters inaccurate responses due to confusing item presentation
- User abandons assessment mid-way due to emotional distress without receiving any support signposting

---

### 5. User Profile

Per DC-002 §3, expanded here for usability analysis purposes.

#### 5.1 Primary User

| Attribute | Specification |
|---|---|
| Age | 18 and over |
| Clinical knowledge | None assumed |
| Health literacy | General adult population — variable |
| Digital literacy | Basic smartphone or desktop browser user |
| Emotional state | May be experiencing distress, anxiety, cognitive difficulties associated with undiagnosed ADHD |
| Motivation | Self-directed — seeking information about their own symptoms |
| Language | English (v1.0) |
| Supervision | None — entirely unsupervised |
| Frequency of use | Typically one-time or infrequent |

#### 5.2 User Subgroups Requiring Specific Consideration

| Subgroup | Specific Consideration |
|---|---|
| Adults with significant inattention symptoms | May have difficulty sustaining attention through 22 items; may misread questions; may rush responses |
| Adults with significant anxiety | Assessment process itself may cause distress; anxiety-related item content may be triggering |
| Adults with comorbid depression | PHQ-9 item 9 pathway is specifically relevant; emotional vulnerability during administration |
| Adults with low health literacy | Score interpretation text must be plain and unambiguous |
| Older adults (65+) | May require larger text; may be less familiar with digital form conventions |
| Adults using assistive technology | Screen reader compatibility is a usability requirement (WCAG 2.1 AA) |
| Adults whose first language is not English | Out of scope v1.0 — noted as v1.1 consideration |

#### 5.3 Secondary User

Healthcare professionals reviewing results shared by a patient. Secondary user usability requirements are limited to:
- Results document clarity and interpretability
- Unambiguous non-clinical formatting (RC-31)
- Clear copyright and screening-status labeling

---

### 6. Use Environment

Per DC-002 §4, expanded for usability analysis.

| Attribute | Specification |
|---|---|
| Physical environment | Home, workplace, or any private location with internet access |
| Noise / distraction | Variable — uncontrolled |
| Lighting | Variable |
| Device | Personal smartphone, tablet, or desktop computer |
| Posture | Seated or mobile — uncontrolled |
| Time pressure | None imposed by device; user sets own pace |
| Interruption | Possible — session persistence not guaranteed |
| Social context | Typically private; may occasionally be in presence of others |

**Implication:** The application must function correctly across highly variable physical conditions. No assumptions can be made about a quiet, focused use environment. This reinforces the need for clear, simple language and unambiguous interactive elements.

---

### 7. Critical Tasks

Critical tasks are those where a use error could result in harm or failure to achieve the intended purpose. Identified by cross-reference with RM-002 hazard list.

| Task ID | Task Description | Linked Hazard | Consequence of Use Error |
|---|---|---|---|
| CT-01 | Confirm age acknowledgement gate | H9 | Under-18 user proceeds with invalid instrument |
| CT-02 | Respond accurately to PHQ-9 item 9 | H5 | Suicidal ideation not detected; crisis screen not triggered |
| CT-03 | Acknowledge crisis screen | H5 | User bypasses crisis resources without engaging |
| CT-04 | Interpret results as screening, not diagnosis | H6 | User self-diagnoses; does not seek clinical consultation |
| CT-05 | Act on positive screen result | H1, H6 | User with ADHD symptoms does not seek clinical follow-up |
| CT-06 | Act on negative screen result appropriately | H1 | User incorrectly assumes ADHD excluded |
| CT-07 | Complete all items without skipping | H7 | Incomplete response set produces incorrect or invalid score |
| CT-08 | Share results only with appropriate parties | H11 | Results shared with employer or insurer |

---

### 8. User Interface Characteristics Relevant to Safety

The following UI characteristics have been identified as safety-relevant and shall be addressed in formative and summative evaluation:

| Characteristic | Safety Relevance |
|---|---|
| Clarity of response options | Ambiguous response options may cause inaccurate responding → scoring error |
| Prominence of disclaimers | Insufficiently prominent disclaimers may fail to prevent misinterpretation of results |
| Crisis screen visibility and tone | Alarm vs. non-alarm balance — too alarming may cause abandonment; too mild may be ignored |
| Acknowledgement gate interaction model | Gate must be obvious enough to notice but not so disruptive as to discourage completion |
| Score display format | Numeric score alone may be misinterpreted; category label and plain-language interpretation are safety controls |
| Results page information hierarchy | If disclaimer is below the fold, it may never be seen on mobile |
| Print/save output formatting | Results document must not resemble a clinical record |
| ASRS threshold item differentiation | Items 4–6 have a higher threshold (Often) than items 1–3 (Sometimes) — question presentation must not imply uniform scoring |

---

### 9. Formative Evaluation Plan

Formative evaluation is conducted during design to identify and address usability problems before summative testing. For a solo developer, formative evaluation is necessarily lightweight but must be documented.

#### 9.1 Formative Activity 1 — Expert Review (Heuristic Evaluation)

**Method:** Structured heuristic evaluation of UI prototype against Nielsen's 10 usability heuristics and IEC 62366-1 Annex C use-related hazard considerations.

**Timing:** After initial UI prototype is complete, before summative testing.

**Evaluator:** Solo developer / PRRC conducting structured self-review against documented heuristics.

**Heuristics checklist:**

| Heuristic | Specific Check for ClarityCheck |
|---|---|
| Visibility of system status | Progress indicator present and accurate on all screens |
| Match between system and real world | Response option language matches how users think about frequency |
| User control and freedom | User can change response; clear how to proceed |
| Consistency and standards | Response options consistent across PHQ-9 and GAD-7 |
| Error prevention | Item skip prevention; gate controls |
| Recognition rather than recall | No requirement to remember previous responses |
| Flexibility and efficiency | Not applicable — single user type, simple linear flow |
| Aesthetic and minimalist design | No extraneous content on question screens; disclaimers not overwhelming |
| Help users recognise and recover from errors | Clear if response not yet selected |
| Help and documentation | IFU accessible from all screens |

**Additional checks specific to ClarityCheck:**

- [ ] Crisis advisory on welcome screen is noticed and read before age gate activation
- [ ] Age gate checkbox is clearly a required action before proceeding
- [ ] Transition between instruments is clear — user knows they are moving to a new section
- [ ] PHQ-9 item 9 wording is clear and not ambiguous in self-report context
- [ ] Crisis screen tone is warm and non-alarmist
- [ ] Results page hierarchy: disclaimer visible before scores on initial screen load
- [ ] Score category labels are not misinterpretable as diagnoses
- [ ] Print/save button purpose is obvious without instruction

**Output:** Formative Evaluation Report — FE-001
**Issues identified shall be:** Classified as critical / major / minor and resolved before summative testing or formally accepted with documented rationale.

---

#### 9.2 Formative Activity 2 — Cognitive Walkthrough

**Method:** Task-based cognitive walkthrough of the complete assessment flow for each critical task (§7). For each critical task step, evaluate:

1. Will the user know what to do at this step?
2. Will the user notice the correct action is available?
3. Will the user understand the feedback that their action was correct?

**Timing:** After formative activity 1 issues are resolved.

**Coverage:**

| Critical Task | Walkthrough Steps |
|---|---|
| CT-01 Age gate | Welcome screen → age checkbox → Begin button activation |
| CT-02 PHQ-9 item 9 | Item display → response selection → advance |
| CT-03 Crisis acknowledgement | Crisis screen display → reading helplines → acknowledgement button |
| CT-04 Results interpretation | Results screen load → disclaimer visibility → category interpretation |
| CT-05 Positive result action | Positive ASRS result → referral advisory → save/print |
| CT-06 Negative result action | Negative ASRS result → sensitivity statement visibility and comprehension |
| CT-07 Item completion | Question screen → response selection → next navigation |
| CT-08 Results sharing | Save/print → disclaimer header visibility in document |

**Output:** Documented walkthrough notes per critical task — attached to FE-001.

---

#### 9.3 Formative Activity 3 — Plain Language Review

**Method:** Review of all user-facing text against plain language criteria. Conducted per NFR-05 requirements and LB-001 design intent.

**Timing:** Before summative testing; after all UI copy is finalised.

**Criteria:**

| Criterion | Target |
|---|---|
| Flesch-Kincaid Grade Level | ≤ 8 overall; ≤ 10 per section |
| Sentence length | Average ≤ 20 words |
| Passive voice | ≤ 10% of sentences |
| Jargon | Zero unexplained clinical terms in user-facing copy |
| Negatives | Double negatives avoided; single negatives clearly understandable |
| Prohibited terms | Per DC-003 §6 prohibited term list |

**Scope:** All user-facing strings: welcome screen, instrument introduction screens, question screens, crisis screen, results screen, results document, in-app IFU.

**Tool:** [Hemingway App or equivalent — to be specified]

**Output:** Plain language review report — attached to FE-001.
**Issues identified:** Must be resolved before summative testing if they affect critical tasks; may be deferred for non-critical copy with documented rationale.

---

### 10. Summative Usability Evaluation Plan

Summative evaluation is conducted on the final or near-final device to validate that the device can be used safely and effectively by the intended user population without unacceptable risk.

#### 10.1 Summative Evaluation Design

**Standard:** IEC 62366-1:2015 clause 5.9

**Method:** Moderated think-aloud usability test with representative participants.

**Timing:** After formative issues resolved; on near-final implementation; before release.

**Evaluator:** Solo developer / PRRC as moderator. Note-taker if available.

---

#### 10.2 Participant Specification

| Parameter | Specification |
|---|---|
| Number | Minimum 5 participants for v1.0 (pragmatic for solo developer; documented limitation) |
| Age | 18–65, at least one participant over 50 |
| Clinical knowledge | None — lay adults only |
| Exclusion criteria | Current acute mental health crisis; healthcare professionals |
| Recruitment | Personal network, ensuring no prior knowledge of ClarityCheck |
| Compensation | Voluntary — no payment for v1.0 |

**Note on sample size:** IEC 62366-1 does not specify a mandatory minimum participant count. 5 participants is consistent with the pragmatic usability testing literature for formative-summative hybrid testing at this device class and risk level, and is a documented and justified approach for a solo developer Class IIa device. This limitation shall be noted in UE-004 and CE-003.

---

#### 10.3 Test Tasks

Participants shall be asked to complete the following tasks with minimal instruction, simulating real-world unsupervised use.

| Task | Instruction to Participant | Critical Task(s) Observed |
|---|---|---|
| T-01 | *"Please use this app as you normally would if you had found it online and wanted to try it."* | CT-01 through CT-07 |
| T-02 | *"You have completed the assessment. Please save or print your results as if you were going to share them with your doctor."* | CT-08 |

**Special test condition — Crisis pathway simulation:**
A separate test session using a confederate scenario (test data pre-populated with PHQ-9 item 9 = 1) shall be used to evaluate crisis screen usability without requiring participants to endorse suicidal ideation themselves. This is a standard methodological approach for testing crisis pathways in digital mental health tools.

| Task | Instruction | Critical Task Observed |
|---|---|---|
| T-03 (Simulated) | Researcher pre-sets PHQ-9 item 9 = 1 in test environment; participant asked to review results pathway | CT-03 |

---

#### 10.4 Data Collection

| Data Type | Method |
|---|---|
| Task completion | Observed — completed / completed with difficulty / failed |
| Use errors | Observed and categorised |
| Close calls | Observed — near-miss use errors |
| Time on task | Recorded per task |
| Verbal data | Think-aloud transcription |
| Comprehension probes | Post-task questions for critical tasks CT-04, CT-05, CT-06 |

**Comprehension probes — CT-04, CT-05, CT-06:**

After T-01, ask each participant:

1. *"In your own words, what does a positive result on the ADHD section mean?"*
   - Acceptable: any response indicating symptoms present / worth discussing with doctor / not a diagnosis
   - Unacceptable: response indicating definitive ADHD diagnosis

2. *"What would you do next if you received a positive result?"*
   - Acceptable: see a doctor / GP / mental health professional
   - Unacceptable: self-diagnose / seek medication without professional consultation

3. *"If you received a negative result, what would that mean to you?"*
   - Acceptable: symptoms below threshold / does not rule out ADHD / would still see doctor if concerned
   - Unacceptable: definitively does not have ADHD / no need to see doctor

**Comprehension probes — Crisis screen (T-03 simulation):**

1. *"What did that screen mean to you?"*
2. *"What would you do after seeing that screen?"*
3. *"Was anything on that screen unclear or confusing?"*

---

#### 10.5 Use Error Classification

Each identified use error shall be classified as follows, consistent with IEC 62366-1:

| Class | Definition | Response |
|---|---|---|
| Use error — critical | Error on a critical task; could result in harm as defined in RM-002 | Must be resolved before release; redesign required |
| Use error — major | Error that prevents task completion or significantly degrades outcome | Resolve before release where practicable |
| Use error — minor | Error that causes delay or frustration but does not affect outcome | Log; address in v1.1 |
| Close call | Near-miss error corrected by user without intervention | Log and review for pattern |
| Observation | Usability difficulty that does not constitute an error | Log for design improvement |

---

#### 10.6 Summative Evaluation Acceptance Criteria

**Critical task acceptance criteria:**

| Critical Task | Acceptance Criterion |
|---|---|
| CT-01 Age gate | 5/5 participants successfully activate age gate before proceeding |
| CT-02 PHQ-9 item 9 | 5/5 participants able to respond to item 9 without confusion about question meaning |
| CT-03 Crisis acknowledgement | 5/5 participants read crisis screen content and activate acknowledgement (T-03 simulation) |
| CT-04 Results interpretation | 4/5 participants correctly identify results as screening not diagnosis in comprehension probe |
| CT-05 Positive result action | 4/5 participants correctly identify clinical consultation as next step |
| CT-06 Negative result action | 4/5 participants correctly identify that negative result does not rule out ADHD |
| CT-07 Item completion | 5/5 participants complete all 22 items without unresolved navigation difficulty |
| CT-08 Results sharing | 4/5 participants notice sharing advisory in results document |

**Overall acceptance criterion:**
- Zero critical use errors observed on CT-01, CT-02, CT-03, CT-07
- No more than 1 major use error across CT-04, CT-05, CT-06, CT-08
- No use error pattern suggesting a systemic design flaw

**If acceptance criteria are not met:**
- Critical use error: halt testing; redesign affected element; repeat summative testing
- Major use error: redesign affected element; targeted re-test with minimum 3 participants on affected task
- Minor use errors: log for v1.1; document in UE-004 as residual usability limitation

---

### 11. Usability Engineering File

The following documents constitute the Usability Engineering File for ClarityCheck v1.0:

| Document | Description | Status |
|---|---|---|
| UE-001 | Usability Engineering Plan (this document) | Draft |
| UE-002 | Intended Use and User Profile (summary) | Derived from §4–§6 above |
| FE-001 | Formative Evaluation Report | Not started — pending prototype |
| UE-003 | Summative Usability Test Report | Not started — pending implementation |
| UE-004 | Summary of Usability Engineering | Not started — final summary document |

**UE-004** is the document submitted as part of the technical documentation for conformity assessment. It summarises the entire usability engineering process, findings, and conclusions.

---

### 12. Relationship to Risk Management

Usability engineering and risk management are tightly coupled for ClarityCheck. The following cross-references apply:

| UE Activity | RM-002 Hazard | RM-003 Risk Control |
|---|---|---|
| CT-01 age gate usability | H9 | RC-26 |
| CT-02 PHQ-9 item 9 | H5 | RC-09 |
| CT-03 crisis screen | H5 | RC-10, RC-11 |
| CT-04 results interpretation | H6 | RC-04, RC-05, RC-14, RC-15 |
| CT-05 positive result action | H1, H6 | RC-01, RC-02, RC-03 |
| CT-06 negative result action | H1 | RC-01, RC-02 |
| CT-07 item completion | H7 | RC-17, RC-19 |
| CT-08 results sharing | H11 | RC-29, RC-30 |

**Process:** Any critical use error identified in summative testing that is linked to a risk control in RM-003 shall trigger a risk management update — RM-002 probability estimate shall be reviewed and RM-003 control revised if the evidence suggests the control is insufficient.

---

### 13. Usability Engineering Activities Timeline

| Activity | Dependency | Planned Timing |
|---|---|---|
| UE-001 Plan (this document) | DC-002, DC-003 | ✅ Now |
| FE-001 Heuristic evaluation | UI prototype available | After initial UI build |
| FE-001 Cognitive walkthrough | UI prototype available | After heuristic evaluation |
| FE-001 Plain language review | All UI copy finalised | After copy complete |
| Formative issues resolved | FE-001 complete | Before summative testing |
| UE-003 Summative testing | Near-final implementation | Before release |
| UE-003 Issues resolved | Summative testing complete | Before release sign-off |
| UE-004 Summary document | UE-003 complete | Release milestone |

---

### 14. Limitations and Mitigations

| Limitation | Mitigation |
|---|---|
| Solo developer as both designer and evaluator — risk of confirmation bias in heuristic review | Structured heuristic checklist followed rigorously; cognitive walkthrough documented step by step; summative testing with external participants mitigates |
| Small summative sample (n=5) | Documented justification; focus on critical tasks; comprehension probes supplement observation; noted as limitation in UE-004 and CE-003 |
| No clinical psychologist involvement in usability design | Clinical reviewer (CE-001 OI-01) to review results screen and crisis screen content as part of VAL-04 |
| No eye-tracking or quantitative usability metrics | Think-aloud and comprehension probes provide sufficient qualitative evidence for this device class and risk level |
| Crisis pathway tested with simulation not live endorsement | Standard methodology for crisis pathway testing; documented and justified in UE-003 |

---

### 15. Review and Approval

| Role | Name | Date | Signature |
|---|---|---|---|
| Author / PRRC | | 2026-04-10 | |

---

### 16. Open Items

| ID | Item | Owner | Due |
|---|---|---|---|
| OI-01 | Identify minimum 5 summative test participants from lay adult population | PRRC | Before summative testing |
| OI-02 | Confirm plain language analysis tool for FE-001 (linked to DC-004 VAL-05) | PRRC | Before formative review |
| OI-03 | Define confederate test scenario for crisis pathway (T-03) — confirm technical approach for pre-setting PHQ-9 item 9 in test environment | PRRC | Before summative testing |
| OI-04 | Clinical reviewer to review crisis screen and results screen content as part of VAL-04 (linked to CE-001 OI-01) | PRRC | Before release |
| OI-05 | FE-001 to be completed post-prototype and findings fed back into RM-002 if new use-related hazards identified | PRRC | After prototype |
