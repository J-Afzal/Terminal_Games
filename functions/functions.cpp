#include "Windows.h"
#include "functions.hpp"
#include <iostream>

bool Get_Number_Of_Players(unsigned int &NumberOfPlayers,
                           const unsigned int &MinPlayers,
                           const unsigned int &MaxPlayers)
{
  std::string Input;
  std::getline(std::cin, Input);

  // Only 0, 1 and 2 players allowed
  if (Input[0] < (char)MinPlayers || Input[0] > (char)MaxPlayers)
    return false;

  else
  {
    NumberOfPlayers = std::stoi(Input, nullptr, 10);
    return true;
  }
}

bool Get_User_Player_Choice(std::string &UserPlayerChoice)
{
  std::string Input;
  std::getline(std::cin, Input);

  Capitalise_Word(Input);

  // Only X and O allowed
  if (Input != "PLAYER ONE" && Input != "PLAYER TWO")
      return false;
  else
  {
    UserPlayerChoice = Input;
    return true;
  }
}

bool Get_AI_Difficulty(std::string &AIDifficulty)
{
  std::string Input;
  std::getline(std::cin, Input);

  Capitalise_Word(Input);

  if (Input != "EASY" && Input != "HARD")
    return false;

  else
  {
    AIDifficulty = Input;
    return true;
  }
}

void Capitalise_Word(std::string &Input)
{
  // Assuming Input contains only letters of unkown capitalisation, if
  // a letter is lower case (>=97) then minus 32 to capitalise it
  for (unsigned int i = 0; i < Input.size(); i++)
  {
    if (Input[i] >= 'a' && Input[i] <= 'z')
      Input[i] -= 32;
  }
}

void Clear_Terminal(void)
{
  // Windows API method taken from https://www.cplusplus.com/articles/4z18T05o
  HANDLE                     hStdOut;
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  DWORD                      count;
  DWORD                      cellCount;
  COORD                      homeCoords = { 0, 0 };

  hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
  if (hStdOut == INVALID_HANDLE_VALUE) return;

  // Get the number of cells in the current buffer
  if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
  cellCount = csbi.dwSize.X *csbi.dwSize.Y;

  // Fill the entire buffer with spaces
  if (!FillConsoleOutputCharacter(
    hStdOut,
    (TCHAR) ' ',
    cellCount,
    homeCoords,
    &count
    )) return;

  // Fill the entire buffer with the current colors and attributes
  if (!FillConsoleOutputAttribute(
    hStdOut,
    csbi.wAttributes,
    cellCount,
    homeCoords,
    &count
    )) return;

  // Move the cursor home
  SetConsoleCursorPosition( hStdOut, homeCoords );
}

void Toggle_Player(std::string &CurrentPlayer)
{
  if (CurrentPlayer == "PLAYER ONE")
    CurrentPlayer = "PLAYER TWO";

  else
    CurrentPlayer = "PLAYER ONE";
}

std::vector<std::string> Generate_Word_List(void)
{
  std::vector<std::string> WordList = {
    "ABILITY",
    "ABLE",
    "ABOUT",
    "ABOVE",
    "ACCEPT",
    "ACCORDING",
    "ACCOUNT",
    "ACROSS",
    "ACT",
    "ACTION",
    "ACTIVITY",
    "ACTUALLY",
    "ADD",
    "ADDRESS",
    "ADMINISTRATION",
    "ADMIT",
    "ADULT",
    "AFFECT",
    "AFTER",
    "AGAIN",
    "AGAINST",
    "AGE",
    "AGENCY",
    "AGENT",
    "AGO",
    "AGREE",
    "AGREEMENT",
    "AHEAD",
    "AIR",
    "ALL",
    "ALLOW",
    "ALMOST",
    "ALONE",
    "ALONG",
    "ALREADY",
    "ALSO",
    "ALTHOUGH",
    "ALWAYS",
    "AMERICAN",
    "AMONG",
    "AMOUNT",
    "ANALYSIS",
    "AND",
    "ANIMAL",
    "ANOTHER",
    "ANSWER",
    "ANY",
    "ANYONE",
    "ANYTHING",
    "APPEAR",
    "APPLY",
    "APPROACH",
    "AREA",
    "ARGUE",
    "ARM",
    "AROUND",
    "ARRIVE",
    "ART",
    "ARTICLE",
    "ARTIST",
    "ASK",
    "ASSUME",
    "ATTACK",
    "ATTENTION",
    "ATTORNEY",
    "AUDIENCE",
    "AUTHOR",
    "AUTHORITY",
    "AVAILABLE",
    "AVOID",
    "AWAY",
    "BABY",
    "BACK",
    "BAD",
    "BAG",
    "BALL",
    "BANK",
    "BAR",
    "BASE",
    "BEAT",
    "BEAUTIFUL",
    "BECAUSE",
    "BECOME",
    "BED",
    "BEFORE",
    "BEGIN",
    "BEHAVIOR",
    "BEHIND",
    "BELIEVE",
    "BENEFIT",
    "BEST",
    "BETTER",
    "BETWEEN",
    "BEYOND",
    "BIG",
    "BILL",
    "BILLION",
    "BIT",
    "BLACK",
    "BLOOD",
    "BLUE",
    "BOARD",
    "BODY",
    "BOOK",
    "BORN",
    "BOTH",
    "BOX",
    "BOY",
    "BREAK",
    "BRING",
    "BROTHER",
    "BUDGET",
    "BUILD",
    "BUILDING",
    "BUSINESS",
    "BUT",
    "BUY",
    "CALL",
    "CAMERA",
    "CAMPAIGN",
    "CAN",
    "CANCER",
    "CANDIDATE",
    "CAPITAL",
    "CAR",
    "CARD",
    "CARE",
    "CAREER",
    "CARRY",
    "CASE",
    "CATCH",
    "CAUSE",
    "CELL",
    "CENTER",
    "CENTRAL",
    "CENTURY",
    "CERTAIN",
    "CERTAINLY",
    "CHAIR",
    "CHALLENGE",
    "CHANCE",
    "CHANGE",
    "CHARACTER",
    "CHARGE",
    "CHECK",
    "CHILD",
    "CHOICE",
    "CHOOSE",
    "CHURCH",
    "CITIZEN",
    "CITY",
    "CIVIL",
    "CLAIM",
    "CLASS",
    "CLEAR",
    "CLEARLY",
    "CLOSE",
    "COACH",
    "COLD",
    "COLLECTION",
    "COLLEGE",
    "COLOR",
    "COME",
    "COMMERCIAL",
    "COMMON",
    "COMMUNITY",
    "COMPANY",
    "COMPARE",
    "COMPUTER",
    "CONCERN",
    "CONDITION",
    "CONFERENCE",
    "CONGRESS",
    "CONSIDER",
    "CONSUMER",
    "CONTAIN",
    "CONTINUE",
    "CONTROL",
    "COST",
    "COULD",
    "COUNTRY",
    "COUPLE",
    "COURSE",
    "COURT",
    "COVER",
    "CREATE",
    "CRIME",
    "CULTURAL",
    "CULTURE",
    "CUP",
    "CURRENT",
    "CUSTOMER",
    "CUT",
    "DARK",
    "DATA",
    "DAUGHTER",
    "DAY",
    "DEAD",
    "DEAL",
    "DEATH",
    "DEBATE",
    "DECADE",
    "DECIDE",
    "DECISION",
    "DEEP",
    "DEFENSE",
    "DEGREE",
    "DEMOCRAT",
    "DEMOCRATIC",
    "DESCRIBE",
    "DESIGN",
    "DESPITE",
    "DETAIL",
    "DETERMINE",
    "DEVELOP",
    "DEVELOPMENT",
    "DIE",
    "DIFFERENCE",
    "DIFFERENT",
    "DIFFICULT",
    "DINNER",
    "DIRECTION",
    "DIRECTOR",
    "DISCOVER",
    "DISCUSS",
    "DISCUSSION",
    "DISEASE",
    "DOCTOR",
    "DOG",
    "DOOR",
    "DOWN",
    "DRAW",
    "DREAM",
    "DRIVE",
    "DROP",
    "DRUG",
    "DURING",
    "EACH",
    "EARLY",
    "EAST",
    "EASY",
    "EAT",
    "ECONOMIC",
    "ECONOMY",
    "EDGE",
    "EDUCATION",
    "EFFECT",
    "EFFORT",
    "EIGHT",
    "EITHER",
    "ELECTION",
    "ELSE",
    "EMPLOYEE",
    "END",
    "ENERGY",
    "ENJOY",
    "ENOUGH",
    "ENTER",
    "ENTIRE",
    "ENVIRONMENT",
    "ENVIRONMENTAL",
    "ESPECIALLY",
    "ESTABLISH",
    "EVEN",
    "EVENING",
    "EVENT",
    "EVER",
    "EVERY",
    "EVERYBODY",
    "EVERYONE",
    "EVERYTHING",
    "EVIDENCE",
    "EXACTLY",
    "EXAMPLE",
    "EXECUTIVE",
    "EXIST",
    "EXPECT",
    "EXPERIENCE",
    "EXPERT",
    "EXPLAIN",
    "EYE",
    "FACE",
    "FACT",
    "FACTOR",
    "FAIL",
    "FALL",
    "FAMILY",
    "FAR",
    "FAST",
    "FATHER",
    "FEAR",
    "FEDERAL",
    "FEEL",
    "FEELING",
    "FEW",
    "FIELD",
    "FIGHT",
    "FIGURE",
    "FILL",
    "FILM",
    "FINAL",
    "FINALLY",
    "FINANCIAL",
    "FIND",
    "FINE",
    "FINGER",
    "FINISH",
    "FIRE",
    "FIRM",
    "FIRST",
    "FISH",
    "FIVE",
    "FLOOR",
    "FLY",
    "FOCUS",
    "FOLLOW",
    "FOOD",
    "FOOT",
    "FOR",
    "FORCE",
    "FOREIGN",
    "FORGET",
    "FORM",
    "FORMER",
    "FORWARD",
    "FOUR",
    "FREE",
    "FRIEND",
    "FROM",
    "FRONT",
    "FULL",
    "FUND",
    "FUTURE",
    "GAME",
    "GARDEN",
    "GAS",
    "GENERAL",
    "GENERATION",
    "GET",
    "GIRL",
    "GIVE",
    "GLASS",
    "GOAL",
    "GOOD",
    "GOVERNMENT",
    "GREAT",
    "GREEN",
    "GROUND",
    "GROUP",
    "GROW",
    "GROWTH",
    "GUESS",
    "GUN",
    "GUY",
    "HAIR",
    "HALF",
    "HAND",
    "HANG",
    "HAPPEN",
    "HAPPY",
    "HARD",
    "HAVE",
    "HEAD",
    "HEALTH",
    "HEAR",
    "HEART",
    "HEAT",
    "HEAVY",
    "HELP",
    "HER",
    "HERE",
    "HERSELF",
    "HIGH",
    "HIM",
    "HIMSELF",
    "HIS",
    "HISTORY",
    "HIT",
    "HOLD",
    "HOME",
    "HOPE",
    "HOSPITAL",
    "HOT",
    "HOTEL",
    "HOUR",
    "HOUSE",
    "HOW",
    "HOWEVER",
    "HUGE",
    "HUMAN",
    "HUNDRED",
    "HUSBAND",
    "IDEA",
    "IDENTIFY",
    "IMAGE",
    "IMAGINE",
    "IMPACT",
    "IMPORTANT",
    "IMPROVE",
    "INCLUDE",
    "INCLUDING",
    "INCREASE",
    "INDEED",
    "INDICATE",
    "INDIVIDUAL",
    "INDUSTRY",
    "INFORMATION",
    "INSIDE",
    "INSTEAD",
    "INSTITUTION",
    "INTEREST",
    "INTERESTING",
    "INTERNATIONAL",
    "INTERVIEW",
    "INTO",
    "INVESTMENT",
    "INVOLVE",
    "ISSUE",
    "ITEM",
    "ITS",
    "ITSELF",
    "JOB",
    "JOIN",
    "JUST",
    "KEEP",
    "KEY",
    "KID",
    "KILL",
    "KIND",
    "KITCHEN",
    "KNOW",
    "KNOWLEDGE",
    "LAND",
    "LANGUAGE",
    "LARGE",
    "LAST",
    "LATE",
    "LATER",
    "LAUGH",
    "LAW",
    "LAWYER",
    "LAY",
    "LEAD",
    "LEADER",
    "LEARN",
    "LEAST",
    "LEAVE",
    "LEFT",
    "LEG",
    "LEGAL",
    "LESS",
    "LET",
    "LETTER",
    "LEVEL",
    "LIE",
    "LIFE",
    "LIGHT",
    "LIKE",
    "LIKELY",
    "LINE",
    "LIST",
    "LISTEN",
    "LITTLE",
    "LIVE",
    "LOCAL",
    "LONG",
    "LOOK",
    "LOSE",
    "LOSS",
    "LOT",
    "LOVE",
    "LOW",
    "MACHINE",
    "MAGAZINE",
    "MAIN",
    "MAINTAIN",
    "MAJOR",
    "MAJORITY",
    "MAKE",
    "MAN",
    "MANAGE",
    "MANAGEMENT",
    "MANAGER",
    "MANY",
    "MARKET",
    "MARRIAGE",
    "MATERIAL",
    "MATTER",
    "MAY",
    "MAYBE",
    "MEAN",
    "MEASURE",
    "MEDIA",
    "MEDICAL",
    "MEET",
    "MEETING",
    "MEMBER",
    "MEMORY",
    "MENTION",
    "MESSAGE",
    "METHOD",
    "MIDDLE",
    "MIGHT",
    "MILITARY",
    "MILLION",
    "MIND",
    "MINUTE",
    "MISS",
    "MISSION",
    "MODEL",
    "MODERN",
    "MOMENT",
    "MONEY",
    "MONTH",
    "MORE",
    "MORNING",
    "MOST",
    "MOTHER",
    "MOUTH",
    "MOVE",
    "MOVEMENT",
    "MOVIE",
    "MRS",
    "MUCH",
    "MUSIC",
    "MUST",
    "MYSELF",
    "NAME",
    "NATION",
    "NATIONAL",
    "NATURAL",
    "NATURE",
    "NEAR",
    "NEARLY",
    "NECESSARY",
    "NEED",
    "NETWORK",
    "NEVER",
    "NEW",
    "NEWS",
    "NEWSPAPER",
    "NEXT",
    "NICE",
    "NIGHT",
    "NONE",
    "NOR",
    "NORTH",
    "NOT",
    "NOTE",
    "NOTHING",
    "NOTICE",
    "NOW",
    "N'T",
    "NUMBER",
    "OCCUR",
    "OFF",
    "OFFER",
    "OFFICE",
    "OFFICER",
    "OFFICIAL",
    "OFTEN",
    "OIL",
    "OLD",
    "ONCE",
    "ONE",
    "ONLY",
    "ONTO",
    "OPEN",
    "OPERATION",
    "OPPORTUNITY",
    "OPTION",
    "ORDER",
    "ORGANIZATION",
    "OTHER",
    "OTHERS",
    "OUR",
    "OUT",
    "OUTSIDE",
    "OVER",
    "OWN",
    "OWNER",
    "PAGE",
    "PAIN",
    "PAINTING",
    "PAPER",
    "PARENT",
    "PART",
    "PARTICIPANT",
    "PARTICULAR",
    "PARTICULARLY",
    "PARTNER",
    "PARTY",
    "PASS",
    "PAST",
    "PATIENT",
    "PATTERN",
    "PAY",
    "PEACE",
    "PEOPLE",
    "PER",
    "PERFORM",
    "PERFORMANCE",
    "PERHAPS",
    "PERIOD",
    "PERSON",
    "PERSONAL",
    "PHONE",
    "PHYSICAL",
    "PICK",
    "PICTURE",
    "PIECE",
    "PLACE",
    "PLAN",
    "PLANT",
    "PLAY",
    "PLAYER",
    "POINT",
    "POLICE",
    "POLICY",
    "POLITICAL",
    "POLITICS",
    "POOR",
    "POPULAR",
    "POPULATION",
    "POSITION",
    "POSITIVE",
    "POSSIBLE",
    "POWER",
    "PRACTICE",
    "PREPARE",
    "PRESENT",
    "PRESIDENT",
    "PRESSURE",
    "PRETTY",
    "PREVENT",
    "PRICE",
    "PRIVATE",
    "PROBABLY",
    "PROBLEM",
    "PROCESS",
    "PRODUCE",
    "PRODUCT",
    "PRODUCTION",
    "PROFESSIONAL",
    "PROFESSOR",
    "PROGRAM",
    "PROJECT",
    "PROPERTY",
    "PROTECT",
    "PROVE",
    "PROVIDE",
    "PUBLIC",
    "PULL",
    "PURPOSE",
    "PUSH",
    "PUT",
    "QUALITY",
    "QUESTION",
    "QUICKLY",
    "QUITE",
    "RACE",
    "RADIO",
    "RAISE",
    "RANGE",
    "RATE",
    "RATHER",
    "REACH",
    "READ",
    "READY",
    "REAL",
    "REALITY",
    "REALIZE",
    "REALLY",
    "REASON",
    "RECEIVE",
    "RECENT",
    "RECENTLY",
    "RECOGNIZE",
    "RECORD",
    "RED",
    "REDUCE",
    "REFLECT",
    "REGION",
    "RELATE",
    "RELATIONSHIP",
    "RELIGIOUS",
    "REMAIN",
    "REMEMBER",
    "REMOVE",
    "REPORT",
    "REPRESENT",
    "REPUBLICAN",
    "REQUIRE",
    "RESEARCH",
    "RESOURCE",
    "RESPOND",
    "RESPONSE",
    "RESPONSIBILITY",
    "REST",
    "RESULT",
    "RETURN",
    "REVEAL",
    "RICH",
    "RIGHT",
    "RISE",
    "RISK",
    "ROAD",
    "ROCK",
    "ROLE",
    "ROOM",
    "RULE",
    "RUN",
    "SAFE",
    "SAME",
    "SAVE",
    "SAY",
    "SCENE",
    "SCHOOL",
    "SCIENCE",
    "SCIENTIST",
    "SCORE",
    "SEA",
    "SEASON",
    "SEAT",
    "SECOND",
    "SECTION",
    "SECURITY",
    "SEE",
    "SEEK",
    "SEEM",
    "SELL",
    "SEND",
    "SENIOR",
    "SENSE",
    "SERIES",
    "SERIOUS",
    "SERVE",
    "SERVICE",
    "SET",
    "SEVEN",
    "SEVERAL",
    "SEX",
    "SEXUAL",
    "SHAKE",
    "SHARE",
    "SHE",
    "SHOOT",
    "SHORT",
    "SHOT",
    "SHOULD",
    "SHOULDER",
    "SHOW",
    "SIDE",
    "SIGN",
    "SIGNIFICANT",
    "SIMILAR",
    "SIMPLE",
    "SIMPLY",
    "SINCE",
    "SING",
    "SINGLE",
    "SISTER",
    "SIT",
    "SITE",
    "SITUATION",
    "SIX",
    "SIZE",
    "SKILL",
    "SKIN",
    "SMALL",
    "SMILE",
    "SOCIAL",
    "SOCIETY",
    "SOLDIER",
    "SOME",
    "SOMEBODY",
    "SOMEONE",
    "SOMETHING",
    "SOMETIMES",
    "SON",
    "SONG",
    "SOON",
    "SORT",
    "SOUND",
    "SOURCE",
    "SOUTH",
    "SOUTHERN",
    "SPACE",
    "SPEAK",
    "SPECIAL",
    "SPECIFIC",
    "SPEECH",
    "SPEND",
    "SPORT",
    "SPRING",
    "STAFF",
    "STAGE",
    "STAND",
    "STANDARD",
    "STAR",
    "START",
    "STATE",
    "STATEMENT",
    "STATION",
    "STAY",
    "STEP",
    "STILL",
    "STOCK",
    "STOP",
    "STORE",
    "STORY",
    "STRATEGY",
    "STREET",
    "STRONG",
    "STRUCTURE",
    "STUDENT",
    "STUDY",
    "STUFF",
    "STYLE",
    "SUBJECT",
    "SUCCESS",
    "SUCCESSFUL",
    "SUCH",
    "SUDDENLY",
    "SUFFER",
    "SUGGEST",
    "SUMMER",
    "SUPPORT",
    "SURE",
    "SURFACE",
    "SYSTEM",
    "TABLE",
    "TAKE",
    "TALK",
    "TASK",
    "TAX",
    "TEACH",
    "TEACHER",
    "TEAM",
    "TECHNOLOGY",
    "TELEVISION",
    "TELL",
    "TEN",
    "TEND",
    "TERM",
    "TEST",
    "THAN",
    "THANK",
    "THAT",
    "THE",
    "THEIR",
    "THEM",
    "THEMSELVES",
    "THEN",
    "THEORY",
    "THERE",
    "THESE",
    "THEY",
    "THING",
    "THINK",
    "THIRD",
    "THIS",
    "THOSE",
    "THOUGH",
    "THOUGHT",
    "THOUSAND",
    "THREAT",
    "THREE",
    "THROUGH",
    "THROUGHOUT",
    "THROW",
    "THUS",
    "TIME",
    "TODAY",
    "TOGETHER",
    "TONIGHT",
    "TOO",
    "TOP",
    "TOTAL",
    "TOUGH",
    "TOWARD",
    "TOWN",
    "TRADE",
    "TRADITIONAL",
    "TRAINING",
    "TRAVEL",
    "TREAT",
    "TREATMENT",
    "TREE",
    "TRIAL",
    "TRIP",
    "TROUBLE",
    "TRUE",
    "TRUTH",
    "TRY",
    "TURN",
    "TWO",
    "TYPE",
    "UNDER",
    "UNDERSTAND",
    "UNIT",
    "UNTIL",
    "UPON",
    "USE",
    "USUALLY",
    "VALUE",
    "VARIOUS",
    "VERY",
    "VICTIM",
    "VIEW",
    "VIOLENCE",
    "VISIT",
    "VOICE",
    "VOTE",
    "WAIT",
    "WALK",
    "WALL",
    "WANT",
    "WAR",
    "WATCH",
    "WATER",
    "WAY",
    "WEAPON",
    "WEAR",
    "WEEK",
    "WEIGHT",
    "WELL",
    "WEST",
    "WESTERN",
    "WHAT",
    "WHATEVER",
    "WHEN",
    "WHERE",
    "WHETHER",
    "WHICH",
    "WHILE",
    "WHITE",
    "WHO",
    "WHOLE",
    "WHOM",
    "WHOSE",
    "WHY",
    "WIDE",
    "WIFE",
    "WILL",
    "WIN",
    "WIND",
    "WINDOW",
    "WISH",
    "WITH",
    "WITHIN",
    "WITHOUT",
    "WOMAN",
    "WONDER",
    "WORD",
    "WORK",
    "WORKER",
    "WORLD",
    "WORRY",
    "WOULD",
    "WRITE",
    "WRITER",
    "WRONG",
    "YARD",
    "YEAH",
    "YEAR",
    "YES",
    "YET",
    "YOU",
    "YOUNG",
    "YOUR",
    "YOURSELF"
  };

  return WordList;
}
