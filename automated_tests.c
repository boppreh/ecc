
#include "ecc.c"

int main() {

	Number p = parse("7fffffff", 4);
	Number result = new_number(4);

	addm(parse("0", 4), parse("0", 4), p, result);
	print(result);
	assert(cmp(result, parse("0", 4)) == 0);

	addm(parse("0", 4), parse("1", 4), p, result);
	print(result);
	assert(cmp(result, parse("1", 4)) == 0);

	addm(parse("1", 4), parse("0", 4), p, result);
	print(result);
	assert(cmp(result, parse("1", 4)) == 0);

	addm(parse("1", 4), parse("1", 4), p, result);
	print(result);
	assert(cmp(result, parse("2", 4)) == 0);

	mulm(parse("0", 4), parse("0", 4), p, result);
	print(result);
	assert(cmp(result, parse("0", 4)) == 0);

	mulm(parse("0", 4), parse("1", 4), p, result);
	print(result);
	assert(cmp(result, parse("0", 4)) == 0);

	mulm(parse("1", 4), parse("0", 4), p, result);
	print(result);
	assert(cmp(result, parse("0", 4)) == 0);

	mulm(parse("1", 4), parse("1", 4), p, result);
	print(result);
	assert(cmp(result, parse("1", 4)) == 0);

	addm(parse("fd3", 4), parse("f662da", 4), p, result);
	print(result);
	assert(cmp(result, parse("f672ad", 4)) == 0);

	addm(parse("7ca63e", 4), parse("ca0159", 4), p, result);
	print(result);
	assert(cmp(result, parse("146a797", 4)) == 0);

	addm(parse("529bd6", 4), parse("a7", 4), p, result);
	print(result);
	assert(cmp(result, parse("529c7d", 4)) == 0);

	addm(parse("3c07ae1", 4), parse("4", 4), p, result);
	print(result);
	assert(cmp(result, parse("3c07ae5", 4)) == 0);

	addm(parse("cfb4ee", 4), parse("f", 4), p, result);
	print(result);
	assert(cmp(result, parse("cfb4fd", 4)) == 0);

	addm(parse("3eb5c44c", 4), parse("d53", 4), p, result);
	print(result);
	assert(cmp(result, parse("3eb5d19f", 4)) == 0);

	addm(parse("5", 4), parse("7a509b5", 4), p, result);
	print(result);
	assert(cmp(result, parse("7a509ba", 4)) == 0);

	addm(parse("6f82405", 4), parse("a7", 4), p, result);
	print(result);
	assert(cmp(result, parse("6f824ac", 4)) == 0);

	addm(parse("8", 4), parse("30", 4), p, result);
	print(result);
	assert(cmp(result, parse("38", 4)) == 0);

	addm(parse("e7a", 4), parse("17cb8b", 4), p, result);
	print(result);
	assert(cmp(result, parse("17da05", 4)) == 0);

	addm(parse("c", 4), parse("ee", 4), p, result);
	print(result);
	assert(cmp(result, parse("fa", 4)) == 0);

	addm(parse("dc", 4), parse("db", 4), p, result);
	print(result);
	assert(cmp(result, parse("1b7", 4)) == 0);

	addm(parse("56cd", 4), parse("b", 4), p, result);
	print(result);
	assert(cmp(result, parse("56d8", 4)) == 0);

	addm(parse("4bd5", 4), parse("28fa7e", 4), p, result);
	print(result);
	assert(cmp(result, parse("294653", 4)) == 0);

	addm(parse("21d7f", 4), parse("d9607", 4), p, result);
	print(result);
	assert(cmp(result, parse("fb386", 4)) == 0);

	addm(parse("6", 4), parse("1f373aa0", 4), p, result);
	print(result);
	assert(cmp(result, parse("1f373aa6", 4)) == 0);

	addm(parse("5e4ec", 4), parse("c3", 4), p, result);
	print(result);
	assert(cmp(result, parse("5e5af", 4)) == 0);

	addm(parse("61f", 4), parse("96f3", 4), p, result);
	print(result);
	assert(cmp(result, parse("9d12", 4)) == 0);

	addm(parse("469586", 4), parse("e2e9", 4), p, result);
	print(result);
	assert(cmp(result, parse("47786f", 4)) == 0);

	addm(parse("26", 4), parse("b689", 4), p, result);
	print(result);
	assert(cmp(result, parse("b6af", 4)) == 0);

	addm(parse("6e3e9", 4), parse("465", 4), p, result);
	print(result);
	assert(cmp(result, parse("6e84e", 4)) == 0);

	addm(parse("76d5f", 4), parse("1dec361a", 4), p, result);
	print(result);
	assert(cmp(result, parse("1df3a379", 4)) == 0);

	addm(parse("6e22e3d7", 4), parse("aa6630", 4), p, result);
	print(result);
	assert(cmp(result, parse("6ecd4a07", 4)) == 0);

	addm(parse("9587", 4), parse("71bbe639", 4), p, result);
	print(result);
	assert(cmp(result, parse("71bc7bc0", 4)) == 0);

	addm(parse("a2", 4), parse("5de4b448", 4), p, result);
	print(result);
	assert(cmp(result, parse("5de4b4ea", 4)) == 0);

	addm(parse("57b61fd7", 4), parse("8", 4), p, result);
	print(result);
	assert(cmp(result, parse("57b61fdf", 4)) == 0);

	addm(parse("828ab", 4), parse("c7446e", 4), p, result);
	print(result);
	assert(cmp(result, parse("cf6d19", 4)) == 0);

	addm(parse("8a0", 4), parse("6edc7", 4), p, result);
	print(result);
	assert(cmp(result, parse("6f667", 4)) == 0);

	addm(parse("c40a", 4), parse("3b", 4), p, result);
	print(result);
	assert(cmp(result, parse("c445", 4)) == 0);

	addm(parse("512f6a", 4), parse("f", 4), p, result);
	print(result);
	assert(cmp(result, parse("512f79", 4)) == 0);

	addm(parse("215a57", 4), parse("fe77", 4), p, result);
	print(result);
	assert(cmp(result, parse("2258ce", 4)) == 0);

	addm(parse("eb", 4), parse("c5b", 4), p, result);
	print(result);
	assert(cmp(result, parse("d46", 4)) == 0);

	addm(parse("f0c6763", 4), parse("23", 4), p, result);
	print(result);
	assert(cmp(result, parse("f0c6786", 4)) == 0);

	addm(parse("1383a183", 4), parse("339eb784", 4), p, result);
	print(result);
	assert(cmp(result, parse("47225907", 4)) == 0);

	addm(parse("6f", 4), parse("24b1c", 4), p, result);
	print(result);
	assert(cmp(result, parse("24b8b", 4)) == 0);

	addm(parse("5e2", 4), parse("d2", 4), p, result);
	print(result);
	assert(cmp(result, parse("6b4", 4)) == 0);

	addm(parse("488e71b", 4), parse("c066", 4), p, result);
	print(result);
	assert(cmp(result, parse("489a781", 4)) == 0);

	addm(parse("515", 4), parse("89b", 4), p, result);
	print(result);
	assert(cmp(result, parse("db0", 4)) == 0);

	addm(parse("4afc", 4), parse("f8ce", 4), p, result);
	print(result);
	assert(cmp(result, parse("143ca", 4)) == 0);

	addm(parse("8d072c", 4), parse("d2e09", 4), p, result);
	print(result);
	assert(cmp(result, parse("9a3535", 4)) == 0);

	addm(parse("11db25", 4), parse("47", 4), p, result);
	print(result);
	assert(cmp(result, parse("11db6c", 4)) == 0);

	addm(parse("af776", 4), parse("62d4a1", 4), p, result);
	print(result);
	assert(cmp(result, parse("6dcc17", 4)) == 0);

	addm(parse("739", 4), parse("d8", 4), p, result);
	print(result);
	assert(cmp(result, parse("811", 4)) == 0);

	addm(parse("2e", 4), parse("f1cd8", 4), p, result);
	print(result);
	assert(cmp(result, parse("f1d06", 4)) == 0);

	addm(parse("27234e", 4), parse("7e40", 4), p, result);
	print(result);
	assert(cmp(result, parse("27a18e", 4)) == 0);

	addm(parse("5", 4), parse("270b", 4), p, result);
	print(result);
	assert(cmp(result, parse("2710", 4)) == 0);

	addm(parse("e0280f", 4), parse("0", 4), p, result);
	print(result);
	assert(cmp(result, parse("e0280f", 4)) == 0);

	addm(parse("20278d7a", 4), parse("eb", 4), p, result);
	print(result);
	assert(cmp(result, parse("20278e65", 4)) == 0);

	addm(parse("6010b7", 4), parse("4c5db14", 4), p, result);
	print(result);
	assert(cmp(result, parse("525ebcb", 4)) == 0);

	addm(parse("46a", 4), parse("ffd93", 4), p, result);
	print(result);
	assert(cmp(result, parse("1001fd", 4)) == 0);

	addm(parse("15", 4), parse("9", 4), p, result);
	print(result);
	assert(cmp(result, parse("1e", 4)) == 0);

	addm(parse("93c", 4), parse("ab", 4), p, result);
	print(result);
	assert(cmp(result, parse("9e7", 4)) == 0);

	addm(parse("f09e2e", 4), parse("8719fd6", 4), p, result);
	print(result);
	assert(cmp(result, parse("9623e04", 4)) == 0);

	addm(parse("cf98219", 4), parse("7ddfa966", 4), p, result);
	print(result);
	assert(cmp(result, parse("ad92b80", 4)) == 0);

	addm(parse("bfb0743", 4), parse("20", 4), p, result);
	print(result);
	assert(cmp(result, parse("bfb0763", 4)) == 0);

	addm(parse("2f73af3", 4), parse("fa0aace", 4), p, result);
	print(result);
	assert(cmp(result, parse("1297e5c1", 4)) == 0);

	addm(parse("1abd7", 4), parse("e5cd6", 4), p, result);
	print(result);
	assert(cmp(result, parse("1008ad", 4)) == 0);

	addm(parse("9418", 4), parse("8a6", 4), p, result);
	print(result);
	assert(cmp(result, parse("9cbe", 4)) == 0);

	addm(parse("606b", 4), parse("2", 4), p, result);
	print(result);
	assert(cmp(result, parse("606d", 4)) == 0);

	addm(parse("e0e0", 4), parse("a96", 4), p, result);
	print(result);
	assert(cmp(result, parse("eb76", 4)) == 0);

	addm(parse("72bd5", 4), parse("16dbef", 4), p, result);
	print(result);
	assert(cmp(result, parse("1e07c4", 4)) == 0);

	addm(parse("a5fb9fc", 4), parse("6b49b03", 4), p, result);
	print(result);
	assert(cmp(result, parse("111454ff", 4)) == 0);

	addm(parse("8732f", 4), parse("77a", 4), p, result);
	print(result);
	assert(cmp(result, parse("87aa9", 4)) == 0);

	addm(parse("36dfd", 4), parse("d4", 4), p, result);
	print(result);
	assert(cmp(result, parse("36ed1", 4)) == 0);

	addm(parse("1124", 4), parse("daf", 4), p, result);
	print(result);
	assert(cmp(result, parse("1ed3", 4)) == 0);

	addm(parse("2f42c28a", 4), parse("a63e3d", 4), p, result);
	print(result);
	assert(cmp(result, parse("2fe900c7", 4)) == 0);

	addm(parse("f", 4), parse("64de615b", 4), p, result);
	print(result);
	assert(cmp(result, parse("64de616a", 4)) == 0);

	addm(parse("fd3", 4), parse("38b23d73", 4), p, result);
	print(result);
	assert(cmp(result, parse("38b24d46", 4)) == 0);

	addm(parse("384", 4), parse("6630b5d0", 4), p, result);
	print(result);
	assert(cmp(result, parse("6630b954", 4)) == 0);

	addm(parse("cfc8d3", 4), parse("d", 4), p, result);
	print(result);
	assert(cmp(result, parse("cfc8e0", 4)) == 0);

	addm(parse("58de2197", 4), parse("38b3a", 4), p, result);
	print(result);
	assert(cmp(result, parse("58e1acd1", 4)) == 0);

	addm(parse("51c", 4), parse("4ab5b08", 4), p, result);
	print(result);
	assert(cmp(result, parse("4ab6024", 4)) == 0);

	addm(parse("a88", 4), parse("962382", 4), p, result);
	print(result);
	assert(cmp(result, parse("962e0a", 4)) == 0);

	addm(parse("fcf", 4), parse("e1590", 4), p, result);
	print(result);
	assert(cmp(result, parse("e255f", 4)) == 0);

	addm(parse("75399", 4), parse("9a79", 4), p, result);
	print(result);
	assert(cmp(result, parse("7ee12", 4)) == 0);

	addm(parse("c3e60bc", 4), parse("1a48", 4), p, result);
	print(result);
	assert(cmp(result, parse("c3e7b04", 4)) == 0);

	addm(parse("be1bf74", 4), parse("27c", 4), p, result);
	print(result);
	assert(cmp(result, parse("be1c1f0", 4)) == 0);

	addm(parse("9e6", 4), parse("53a30", 4), p, result);
	print(result);
	assert(cmp(result, parse("54416", 4)) == 0);

	addm(parse("5cc42f8", 4), parse("1bbc7def", 4), p, result);
	print(result);
	assert(cmp(result, parse("2188c0e7", 4)) == 0);

	addm(parse("18", 4), parse("693780a4", 4), p, result);
	print(result);
	assert(cmp(result, parse("693780bc", 4)) == 0);

	addm(parse("48", 4), parse("2e0d", 4), p, result);
	print(result);
	assert(cmp(result, parse("2e55", 4)) == 0);

	addm(parse("4bb73", 4), parse("a9b24b0", 4), p, result);
	print(result);
	assert(cmp(result, parse("a9fe023", 4)) == 0);

	addm(parse("37cf9b11", 4), parse("6", 4), p, result);
	print(result);
	assert(cmp(result, parse("37cf9b17", 4)) == 0);

	addm(parse("c803e42", 4), parse("a4c7a6d", 4), p, result);
	print(result);
	assert(cmp(result, parse("16ccb8af", 4)) == 0);

	addm(parse("7f", 4), parse("17dc", 4), p, result);
	print(result);
	assert(cmp(result, parse("185b", 4)) == 0);

	addm(parse("1dde733a", 4), parse("d4bf55", 4), p, result);
	print(result);
	assert(cmp(result, parse("1eb3328f", 4)) == 0);

	addm(parse("acf", 4), parse("f3fd38e", 4), p, result);
	print(result);
	assert(cmp(result, parse("f3fde5d", 4)) == 0);

	addm(parse("83a06ad", 4), parse("d8e8242", 4), p, result);
	print(result);
	assert(cmp(result, parse("15c888ef", 4)) == 0);

	addm(parse("6a072d3c", 4), parse("76db3", 4), p, result);
	print(result);
	assert(cmp(result, parse("6a0e9aef", 4)) == 0);

	addm(parse("7a43cf25", 4), parse("206fe0ae", 4), p, result);
	print(result);
	assert(cmp(result, parse("1ab3afd4", 4)) == 0);

	addm(parse("9dc2", 4), parse("559bc2c", 4), p, result);
	print(result);
	assert(cmp(result, parse("55a59ee", 4)) == 0);

	addm(parse("6f", 4), parse("526", 4), p, result);
	print(result);
	assert(cmp(result, parse("595", 4)) == 0);

	addm(parse("bbf", 4), parse("69b", 4), p, result);
	print(result);
	assert(cmp(result, parse("125a", 4)) == 0);

	addm(parse("73d471", 4), parse("a3674d", 4), p, result);
	print(result);
	assert(cmp(result, parse("1173bbe", 4)) == 0);

	addm(parse("4f006", 4), parse("fb131", 4), p, result);
	print(result);
	assert(cmp(result, parse("14a137", 4)) == 0);

	addm(parse("3", 4), parse("646", 4), p, result);
	print(result);
	assert(cmp(result, parse("649", 4)) == 0);

	addm(parse("d", 4), parse("a1a", 4), p, result);
	print(result);
	assert(cmp(result, parse("a27", 4)) == 0);

	addm(parse("3", 4), parse("1b034", 4), p, result);
	print(result);
	assert(cmp(result, parse("1b037", 4)) == 0);

	addm(parse("659056", 4), parse("6", 4), p, result);
	print(result);
	assert(cmp(result, parse("65905c", 4)) == 0);

	addm(parse("25f8d4d", 4), parse("c637", 4), p, result);
	print(result);
	assert(cmp(result, parse("2605384", 4)) == 0);

	subm(parse("b33a", 4), parse("d4f5", 4), p, result);
	print(result);
	assert(cmp(result, parse("7fffde44", 4)) == 0);

	subm(parse("9d44f7", 4), parse("3", 4), p, result);
	print(result);
	assert(cmp(result, parse("9d44f4", 4)) == 0);

	subm(parse("8ef9950", 4), parse("a28dd", 4), p, result);
	print(result);
	assert(cmp(result, parse("8e57073", 4)) == 0);

	subm(parse("e919f75", 4), parse("2abdc72", 4), p, result);
	print(result);
	assert(cmp(result, parse("be5c303", 4)) == 0);

	subm(parse("fae", 4), parse("e31", 4), p, result);
	print(result);
	assert(cmp(result, parse("17d", 4)) == 0);

	subm(parse("a", 4), parse("6d", 4), p, result);
	print(result);
	assert(cmp(result, parse("7fffff9c", 4)) == 0);

	subm(parse("43c948", 4), parse("f3", 4), p, result);
	print(result);
	assert(cmp(result, parse("43c855", 4)) == 0);

	subm(parse("116", 4), parse("4b5", 4), p, result);
	print(result);
	assert(cmp(result, parse("7ffffc60", 4)) == 0);

	subm(parse("b", 4), parse("f30f", 4), p, result);
	print(result);
	assert(cmp(result, parse("7fff0cfb", 4)) == 0);

	subm(parse("b", 4), parse("27d64995", 4), p, result);
	print(result);
	assert(cmp(result, parse("5829b675", 4)) == 0);

	subm(parse("179e", 4), parse("a22", 4), p, result);
	print(result);
	assert(cmp(result, parse("d7c", 4)) == 0);

	subm(parse("8d6", 4), parse("ef9", 4), p, result);
	print(result);
	assert(cmp(result, parse("7ffff9dc", 4)) == 0);

	subm(parse("d7", 4), parse("32e40f4", 4), p, result);
	print(result);
	assert(cmp(result, parse("7cd1bfe2", 4)) == 0);

	subm(parse("6f5", 4), parse("76c39b0c", 4), p, result);
	print(result);
	assert(cmp(result, parse("93c6be8", 4)) == 0);

	subm(parse("1a4c2", 4), parse("70", 4), p, result);
	print(result);
	assert(cmp(result, parse("1a452", 4)) == 0);

	subm(parse("79b", 4), parse("77788f24", 4), p, result);
	print(result);
	assert(cmp(result, parse("8877876", 4)) == 0);

	subm(parse("f9f", 4), parse("3c2b9f80", 4), p, result);
	print(result);
	assert(cmp(result, parse("43d4701e", 4)) == 0);

	subm(parse("4", 4), parse("c", 4), p, result);
	print(result);
	assert(cmp(result, parse("7ffffff7", 4)) == 0);

	subm(parse("83b4f8b", 4), parse("60c", 4), p, result);
	print(result);
	assert(cmp(result, parse("83b497f", 4)) == 0);

	subm(parse("623dab8d", 4), parse("ecdc", 4), p, result);
	print(result);
	assert(cmp(result, parse("623cbeb1", 4)) == 0);

	subm(parse("c37c", 4), parse("4e24d", 4), p, result);
	print(result);
	assert(cmp(result, parse("7ffbe12e", 4)) == 0);

	subm(parse("bf0aa", 4), parse("93e6", 4), p, result);
	print(result);
	assert(cmp(result, parse("b5cc4", 4)) == 0);

	subm(parse("98000", 4), parse("eae9f5c", 4), p, result);
	print(result);
	assert(cmp(result, parse("715ae0a3", 4)) == 0);

	subm(parse("2b78c", 4), parse("f", 4), p, result);
	print(result);
	assert(cmp(result, parse("2b77d", 4)) == 0);

	subm(parse("517", 4), parse("9f829d", 4), p, result);
	print(result);
	assert(cmp(result, parse("7f608279", 4)) == 0);

	subm(parse("26c9026", 4), parse("5478d", 4), p, result);
	print(result);
	assert(cmp(result, parse("2674899", 4)) == 0);

	subm(parse("eda1d93", 4), parse("9cf9f", 4), p, result);
	print(result);
	assert(cmp(result, parse("ed04df4", 4)) == 0);

	subm(parse("2afe0df6", 4), parse("15220e39", 4), p, result);
	print(result);
	assert(cmp(result, parse("15dbffbd", 4)) == 0);

	subm(parse("e23e8d", 4), parse("41e6683e", 4), p, result);
	print(result);
	assert(cmp(result, parse("3efbd64e", 4)) == 0);

	subm(parse("202bb807", 4), parse("285ec0", 4), p, result);
	print(result);
	assert(cmp(result, parse("20035947", 4)) == 0);

	subm(parse("6e528e71", 4), parse("c", 4), p, result);
	print(result);
	assert(cmp(result, parse("6e528e65", 4)) == 0);

	subm(parse("3ec", 4), parse("1d95", 4), p, result);
	print(result);
	assert(cmp(result, parse("7fffe656", 4)) == 0);

	subm(parse("f", 4), parse("4dd", 4), p, result);
	print(result);
	assert(cmp(result, parse("7ffffb31", 4)) == 0);

	subm(parse("7", 4), parse("1cf68b", 4), p, result);
	print(result);
	assert(cmp(result, parse("7fe3097b", 4)) == 0);

	subm(parse("8f", 4), parse("94a", 4), p, result);
	print(result);
	assert(cmp(result, parse("7ffff744", 4)) == 0);

	subm(parse("1a703", 4), parse("f2", 4), p, result);
	print(result);
	assert(cmp(result, parse("1a611", 4)) == 0);

	subm(parse("8", 4), parse("65c", 4), p, result);
	print(result);
	assert(cmp(result, parse("7ffff9ab", 4)) == 0);

	subm(parse("c26459", 4), parse("9e7d", 4), p, result);
	print(result);
	assert(cmp(result, parse("c1c5dc", 4)) == 0);

	subm(parse("f668a", 4), parse("df7ac24", 4), p, result);
	print(result);
	assert(cmp(result, parse("7217ba65", 4)) == 0);

	subm(parse("a", 4), parse("9cc799a", 4), p, result);
	print(result);
	assert(cmp(result, parse("7633866f", 4)) == 0);

	subm(parse("d8", 4), parse("750c08", 4), p, result);
	print(result);
	assert(cmp(result, parse("7f8af4cf", 4)) == 0);

	subm(parse("720e74", 4), parse("7e", 4), p, result);
	print(result);
	assert(cmp(result, parse("720df6", 4)) == 0);

	subm(parse("1b1e205b", 4), parse("6d0725", 4), p, result);
	print(result);
	assert(cmp(result, parse("1ab11936", 4)) == 0);

	subm(parse("4", 4), parse("285daae6", 4), p, result);
	print(result);
	assert(cmp(result, parse("57a2551d", 4)) == 0);

	subm(parse("79fa63c", 4), parse("0", 4), p, result);
	print(result);
	assert(cmp(result, parse("79fa63c", 4)) == 0);

	subm(parse("9f82a87", 4), parse("214dee", 4), p, result);
	print(result);
	assert(cmp(result, parse("9d6dc99", 4)) == 0);

	subm(parse("c437e1", 4), parse("b90e79", 4), p, result);
	print(result);
	assert(cmp(result, parse("b2968", 4)) == 0);

	subm(parse("20f2b65", 4), parse("74903a", 4), p, result);
	print(result);
	assert(cmp(result, parse("19a9b2b", 4)) == 0);

	subm(parse("ad0ee", 4), parse("1e", 4), p, result);
	print(result);
	assert(cmp(result, parse("ad0d0", 4)) == 0);

	subm(parse("dc", 4), parse("a2b0", 4), p, result);
	print(result);
	assert(cmp(result, parse("7fff5e2b", 4)) == 0);

	subm(parse("4d57", 4), parse("b", 4), p, result);
	print(result);
	assert(cmp(result, parse("4d4c", 4)) == 0);

	subm(parse("8486", 4), parse("2c0", 4), p, result);
	print(result);
	assert(cmp(result, parse("81c6", 4)) == 0);

	subm(parse("5e46", 4), parse("607a74d4", 4), p, result);
	print(result);
	assert(cmp(result, parse("1f85e971", 4)) == 0);

	subm(parse("f5", 4), parse("3c6c7", 4), p, result);
	print(result);
	assert(cmp(result, parse("7ffc3a2d", 4)) == 0);

	subm(parse("4c", 4), parse("d", 4), p, result);
	print(result);
	assert(cmp(result, parse("3f", 4)) == 0);

	subm(parse("c3df7", 4), parse("77b", 4), p, result);
	print(result);
	assert(cmp(result, parse("c367c", 4)) == 0);

	subm(parse("e1fc1a8", 4), parse("557ec", 4), p, result);
	print(result);
	assert(cmp(result, parse("e1a69bc", 4)) == 0);

	subm(parse("68dce6a", 4), parse("428", 4), p, result);
	print(result);
	assert(cmp(result, parse("68dca42", 4)) == 0);

	subm(parse("47a731f8", 4), parse("261b735", 4), p, result);
	print(result);
	assert(cmp(result, parse("45457ac3", 4)) == 0);

	subm(parse("a6c2f", 4), parse("7f84a5", 4), p, result);
	print(result);
	assert(cmp(result, parse("7f8ae789", 4)) == 0);

	subm(parse("fd8", 4), parse("a8", 4), p, result);
	print(result);
	assert(cmp(result, parse("f30", 4)) == 0);

	subm(parse("d1217e", 4), parse("4e7c7f5", 4), p, result);
	print(result);
	assert(cmp(result, parse("7be95988", 4)) == 0);

	subm(parse("618c0f38", 4), parse("9", 4), p, result);
	print(result);
	assert(cmp(result, parse("618c0f2f", 4)) == 0);

	subm(parse("4", 4), parse("5ff65da", 4), p, result);
	print(result);
	assert(cmp(result, parse("7a009a29", 4)) == 0);

	subm(parse("5f9c35", 4), parse("dc7", 4), p, result);
	print(result);
	assert(cmp(result, parse("5f8e6e", 4)) == 0);

	subm(parse("0", 4), parse("9", 4), p, result);
	print(result);
	assert(cmp(result, parse("7ffffff6", 4)) == 0);

	subm(parse("bbe", 4), parse("4d", 4), p, result);
	print(result);
	assert(cmp(result, parse("b71", 4)) == 0);

	subm(parse("f806", 4), parse("2c", 4), p, result);
	print(result);
	assert(cmp(result, parse("f7da", 4)) == 0);

	subm(parse("8", 4), parse("914c", 4), p, result);
	print(result);
	assert(cmp(result, parse("7fff6ebb", 4)) == 0);

	subm(parse("443", 4), parse("bec", 4), p, result);
	print(result);
	assert(cmp(result, parse("7ffff856", 4)) == 0);

	subm(parse("5ba9e210", 4), parse("a", 4), p, result);
	print(result);
	assert(cmp(result, parse("5ba9e206", 4)) == 0);

	subm(parse("4", 4), parse("5693fdb", 4), p, result);
	print(result);
	assert(cmp(result, parse("7a96c028", 4)) == 0);

	subm(parse("2d2890c2", 4), parse("6", 4), p, result);
	print(result);
	assert(cmp(result, parse("2d2890bc", 4)) == 0);

	subm(parse("7", 4), parse("2a26a570", 4), p, result);
	print(result);
	assert(cmp(result, parse("55d95a96", 4)) == 0);

	subm(parse("e73000c", 4), parse("6ea846a", 4), p, result);
	print(result);
	assert(cmp(result, parse("7887ba2", 4)) == 0);

	subm(parse("2e", 4), parse("112e57", 4), p, result);
	print(result);
	assert(cmp(result, parse("7feed1d6", 4)) == 0);

	subm(parse("4102f", 4), parse("d99f", 4), p, result);
	print(result);
	assert(cmp(result, parse("33690", 4)) == 0);

	subm(parse("9", 4), parse("8ae75", 4), p, result);
	print(result);
	assert(cmp(result, parse("7ff75193", 4)) == 0);

	subm(parse("40d", 4), parse("9", 4), p, result);
	print(result);
	assert(cmp(result, parse("404", 4)) == 0);

	subm(parse("df3c11a", 4), parse("9451de", 4), p, result);
	print(result);
	assert(cmp(result, parse("d5f6f3c", 4)) == 0);

	subm(parse("b", 4), parse("d23ec3", 4), p, result);
	print(result);
	assert(cmp(result, parse("7f2dc147", 4)) == 0);

	subm(parse("20cf747", 4), parse("82c", 4), p, result);
	print(result);
	assert(cmp(result, parse("20cef1b", 4)) == 0);

	subm(parse("1", 4), parse("33", 4), p, result);
	print(result);
	assert(cmp(result, parse("7fffffcd", 4)) == 0);

	subm(parse("b49", 4), parse("441e", 4), p, result);
	print(result);
	assert(cmp(result, parse("7fffc72a", 4)) == 0);

	subm(parse("330", 4), parse("24b2da67", 4), p, result);
	print(result);
	assert(cmp(result, parse("5b4d28c8", 4)) == 0);

	subm(parse("40a14fe8", 4), parse("3a66f52", 4), p, result);
	print(result);
	assert(cmp(result, parse("3cfae096", 4)) == 0);

	subm(parse("8e7847", 4), parse("c", 4), p, result);
	print(result);
	assert(cmp(result, parse("8e783b", 4)) == 0);

	subm(parse("12c", 4), parse("1", 4), p, result);
	print(result);
	assert(cmp(result, parse("12b", 4)) == 0);

	subm(parse("588fa53f", 4), parse("6839ec", 4), p, result);
	print(result);
	assert(cmp(result, parse("58276b53", 4)) == 0);

	subm(parse("e9b3", 4), parse("31b54d48", 4), p, result);
	print(result);
	assert(cmp(result, parse("4e4b9c6a", 4)) == 0);

	subm(parse("e0b6753", 4), parse("9a", 4), p, result);
	print(result);
	assert(cmp(result, parse("e0b66b9", 4)) == 0);

	subm(parse("277acfee", 4), parse("92e635", 4), p, result);
	print(result);
	assert(cmp(result, parse("26e7e9b9", 4)) == 0);

	subm(parse("592", 4), parse("3", 4), p, result);
	print(result);
	assert(cmp(result, parse("58f", 4)) == 0);

	subm(parse("6e379f84", 4), parse("d", 4), p, result);
	print(result);
	assert(cmp(result, parse("6e379f77", 4)) == 0);

	subm(parse("d", 4), parse("61a7280", 4), p, result);
	print(result);
	assert(cmp(result, parse("79e58d8c", 4)) == 0);

	subm(parse("c", 4), parse("f", 4), p, result);
	print(result);
	assert(cmp(result, parse("7ffffffc", 4)) == 0);

	subm(parse("df615", 4), parse("392", 4), p, result);
	print(result);
	assert(cmp(result, parse("df283", 4)) == 0);

	subm(parse("70256574", 4), parse("f62308", 4), p, result);
	print(result);
	assert(cmp(result, parse("6f2f426c", 4)) == 0);

	subm(parse("ffe", 4), parse("3", 4), p, result);
	print(result);
	assert(cmp(result, parse("ffb", 4)) == 0);

	subm(parse("dd", 4), parse("535", 4), p, result);
	print(result);
	assert(cmp(result, parse("7ffffba7", 4)) == 0);

	mulm(parse("71", 4), parse("775e", 4), p, result);
	print(result);
	assert(cmp(result, parse("34b07e", 4)) == 0);

	mulm(parse("30", 4), parse("8f", 4), p, result);
	print(result);
	assert(cmp(result, parse("1ad0", 4)) == 0);

	mulm(parse("f3a15e5", 4), parse("bd6dd", 4), p, result);
	print(result);
	assert(cmp(result, parse("244abd3e", 4)) == 0);

	mulm(parse("41e9745", 4), parse("b1c5", 4), p, result);
	print(result);
	assert(cmp(result, parse("522122d1", 4)) == 0);

	mulm(parse("d6", 4), parse("5f05b", 4), p, result);
	print(result);
	assert(cmp(result, parse("4f6ec12", 4)) == 0);

	mulm(parse("0", 4), parse("d2313c", 4), p, result);
	print(result);
	assert(cmp(result, parse("0", 4)) == 0);

	mulm(parse("c", 4), parse("88cef6d", 4), p, result);
	print(result);
	assert(cmp(result, parse("669b391c", 4)) == 0);

	mulm(parse("79a79", 4), parse("799f", 4), p, result);
	print(result);
	assert(cmp(result, parse("1cbc222e", 4)) == 0);

	mulm(parse("453f2", 4), parse("6faa533d", 4), p, result);
	print(result);
	assert(cmp(result, parse("14f73d38", 4)) == 0);

	mulm(parse("adad1e", 4), parse("2ef7e9", 4), p, result);
	print(result);
	assert(cmp(result, parse("4b7ec208", 4)) == 0);

	mulm(parse("2a41", 4), parse("584f85f", 4), p, result);
	print(result);
	assert(cmp(result, parse("3782a7f1", 4)) == 0);

	mulm(parse("cbf747a", 4), parse("5", 4), p, result);
	print(result);
	assert(cmp(result, parse("3fbd4662", 4)) == 0);

	mulm(parse("c", 4), parse("f8c9398", 4), p, result);
	print(result);
	assert(cmp(result, parse("3a96eb21", 4)) == 0);

	mulm(parse("c7ba", 4), parse("b502", 4), p, result);
	print(result);
	assert(cmp(result, parse("d381175", 4)) == 0);

	mulm(parse("69d7ac55", 4), parse("2c9221", 4), p, result);
	print(result);
	assert(cmp(result, parse("43d68bed", 4)) == 0);

	mulm(parse("688c40", 4), parse("1dc", 4), p, result);
	print(result);
	assert(cmp(result, parse("4264c701", 4)) == 0);

	mulm(parse("df", 4), parse("55", 4), p, result);
	print(result);
	assert(cmp(result, parse("4a0b", 4)) == 0);

	mulm(parse("db6b443", 4), parse("18ac52", 4), p, result);
	print(result);
	assert(cmp(result, parse("bed662e", 4)) == 0);

	mulm(parse("ddaf", 4), parse("8e3", 4), p, result);
	print(result);
	assert(cmp(result, parse("7b20a2d", 4)) == 0);

	mulm(parse("34a0e", 4), parse("7ca9d", 4), p, result);
	print(result);
	assert(cmp(result, parse("20d576c9", 4)) == 0);

	mulm(parse("b", 4), parse("2376b", 4), p, result);
	print(result);
	assert(cmp(result, parse("186199", 4)) == 0);

	mulm(parse("c5df04b", 4), parse("30d", 4), p, result);
	print(result);
	assert(cmp(result, parse("3a96151a", 4)) == 0);

	mulm(parse("3cc9d3c4", 4), parse("9d", 4), p, result);
	print(result);
	assert(cmp(result, parse("47c6df7e", 4)) == 0);

	mulm(parse("2", 4), parse("57be71ac", 4), p, result);
	print(result);
	assert(cmp(result, parse("2f7ce359", 4)) == 0);

	mulm(parse("e2294", 4), parse("e9", 4), p, result);
	print(result);
	assert(cmp(result, parse("cdd78b4", 4)) == 0);

	mulm(parse("4799", 4), parse("d", 4), p, result);
	print(result);
	assert(cmp(result, parse("3a2c5", 4)) == 0);

	mulm(parse("d4461a", 4), parse("d25ff4", 4), p, result);
	print(result);
	assert(cmp(result, parse("11abd3aa", 4)) == 0);

	mulm(parse("5b4", 4), parse("269e628e", 4), p, result);
	print(result);
	assert(cmp(result, parse("3f4a1390", 4)) == 0);

	mulm(parse("1665edbc", 4), parse("ce1d9", 4), p, result);
	print(result);
	assert(cmp(result, parse("372b016f", 4)) == 0);

	mulm(parse("394b75ad", 4), parse("89c46", 4), p, result);
	print(result);
	assert(cmp(result, parse("53c373f8", 4)) == 0);

	mulm(parse("7b64b271", 4), parse("7fbf264d", 4), p, result);
	print(result);
	assert(cmp(result, parse("3c3ba038", 4)) == 0);

	mulm(parse("28d27aad", 4), parse("870", 4), p, result);
	print(result);
	assert(cmp(result, parse("6feb1660", 4)) == 0);

	mulm(parse("955c9", 4), parse("6f43ecbf", 4), p, result);
	print(result);
	assert(cmp(result, parse("3caf6a4f", 4)) == 0);

	mulm(parse("7d5c0", 4), parse("69313aa", 4), p, result);
	print(result);
	assert(cmp(result, parse("57519885", 4)) == 0);

	mulm(parse("748", 4), parse("483422", 4), p, result);
	print(result);
	assert(cmp(result, parse("dbb9794", 4)) == 0);

	mulm(parse("ca", 4), parse("36d364f", 4), p, result);
	print(result);
	assert(cmp(result, parse("342cda5b", 4)) == 0);

	mulm(parse("7d8", 4), parse("1c9adb8", 4), p, result);
	print(result);
	assert(cmp(result, parse("5ea9b5c", 4)) == 0);

	mulm(parse("29", 4), parse("89", 4), p, result);
	print(result);
	assert(cmp(result, parse("15f1", 4)) == 0);

	mulm(parse("58", 4), parse("158bf", 4), p, result);
	print(result);
	assert(cmp(result, parse("7681a8", 4)) == 0);

	mulm(parse("b847b", 4), parse("aa1", 4), p, result);
	print(result);
	assert(cmp(result, parse("7a6b1f5b", 4)) == 0);

	mulm(parse("9", 4), parse("9715c04", 4), p, result);
	print(result);
	assert(cmp(result, parse("54fc3c24", 4)) == 0);

	mulm(parse("bae2636", 4), parse("3b", 4), p, result);
	print(result);
	assert(cmp(result, parse("3122ce77", 4)) == 0);

	mulm(parse("5", 4), parse("b4", 4), p, result);
	print(result);
	assert(cmp(result, parse("384", 4)) == 0);

	mulm(parse("d9", 4), parse("a", 4), p, result);
	print(result);
	assert(cmp(result, parse("87a", 4)) == 0);

	mulm(parse("45", 4), parse("99", 4), p, result);
	print(result);
	assert(cmp(result, parse("293d", 4)) == 0);

	mulm(parse("544e691e", 4), parse("79", 4), p, result);
	print(result);
	assert(cmp(result, parse("590faf7d", 4)) == 0);

	mulm(parse("b794049", 4), parse("3f100f2", 4), p, result);
	print(result);
	assert(cmp(result, parse("38b236e4", 4)) == 0);

	mulm(parse("81", 4), parse("be74483", 4), p, result);
	print(result);
	assert(cmp(result, parse("7f89860e", 4)) == 0);

	mulm(parse("f5", 4), parse("7b90b0", 4), p, result);
	print(result);
	assert(cmp(result, parse("76417870", 4)) == 0);

	mulm(parse("b5", 4), parse("338d98", 4), p, result);
	print(result);
	assert(cmp(result, parse("24731c78", 4)) == 0);

	mulm(parse("7391", 4), parse("794019", 4), p, result);
	print(result);
	assert(cmp(result, parse("3c788996", 4)) == 0);

	mulm(parse("2a70fd", 4), parse("5", 4), p, result);
	print(result);
	assert(cmp(result, parse("d434f1", 4)) == 0);

	mulm(parse("2", 4), parse("46b39eb", 4), p, result);
	print(result);
	assert(cmp(result, parse("8d673d6", 4)) == 0);

	mulm(parse("d", 4), parse("f", 4), p, result);
	print(result);
	assert(cmp(result, parse("c3", 4)) == 0);

	mulm(parse("f07c55", 4), parse("817d45", 4), p, result);
	print(result);
	assert(cmp(result, parse("545cf731", 4)) == 0);

	mulm(parse("f7", 4), parse("7c2", 4), p, result);
	print(result);
	assert(cmp(result, parse("77c2e", 4)) == 0);

	mulm(parse("a45af", 4), parse("e919", 4), p, result);
	print(result);
	assert(cmp(result, parse("5a6d1529", 4)) == 0);

	mulm(parse("5706", 4), parse("385e", 4), p, result);
	print(result);
	assert(cmp(result, parse("13294434", 4)) == 0);

	mulm(parse("a7ab93", 4), parse("667283", 4), p, result);
	print(result);
	assert(cmp(result, parse("5cc6c86b", 4)) == 0);

	mulm(parse("9251da", 4), parse("91", 4), p, result);
	print(result);
	assert(cmp(result, parse("52e05c7a", 4)) == 0);

	mulm(parse("c", 4), parse("2539844", 4), p, result);
	print(result);
	assert(cmp(result, parse("1beb2330", 4)) == 0);

	mulm(parse("a933", 4), parse("ffb", 4), p, result);
	print(result);
	assert(cmp(result, parse("a8fe201", 4)) == 0);

	mulm(parse("6b2c5be2", 4), parse("a790c07", 4), p, result);
	print(result);
	assert(cmp(result, parse("4d1bec5c", 4)) == 0);

	mulm(parse("98b96d", 4), parse("e85f70a", 4), p, result);
	print(result);
	assert(cmp(result, parse("2c91bd61", 4)) == 0);

	mulm(parse("1d79", 4), parse("44", 4), p, result);
	print(result);
	assert(cmp(result, parse("7d424", 4)) == 0);

	mulm(parse("6b9", 4), parse("6b4807b8", 4), p, result);
	print(result);
	assert(cmp(result, parse("373be99a", 4)) == 0);

	mulm(parse("5", 4), parse("2b6655a", 4), p, result);
	print(result);
	assert(cmp(result, parse("d8ffac2", 4)) == 0);

	mulm(parse("66", 4), parse("8e4107e", 4), p, result);
	print(result);
	assert(cmp(result, parse("ade923b", 4)) == 0);

	mulm(parse("9969a16", 4), parse("dbf959a", 4), p, result);
	print(result);
	assert(cmp(result, parse("1b924d1", 4)) == 0);

	mulm(parse("ba7c", 4), parse("35e6f", 4), p, result);
	print(result);
	assert(cmp(result, parse("743e63c8", 4)) == 0);

	mulm(parse("5", 4), parse("dd", 4), p, result);
	print(result);
	assert(cmp(result, parse("451", 4)) == 0);

	mulm(parse("191d5b0e", 4), parse("4987cc", 4), p, result);
	print(result);
	assert(cmp(result, parse("75755e8a", 4)) == 0);

	mulm(parse("634fa36", 4), parse("98196f", 4), p, result);
	print(result);
	assert(cmp(result, parse("6d7f238e", 4)) == 0);

	mulm(parse("fea", 4), parse("8c611", 4), p, result);
	print(result);
	assert(cmp(result, parse("ba00a8b", 4)) == 0);

	mulm(parse("b3557b1", 4), parse("edd", 4), p, result);
	print(result);
	assert(cmp(result, parse("17d8631a", 4)) == 0);

	mulm(parse("b21d5", 4), parse("9e122df", 4), p, result);
	print(result);
	assert(cmp(result, parse("3d669e80", 4)) == 0);

	mulm(parse("ff53c", 4), parse("e6", 4), p, result);
	print(result);
	assert(cmp(result, parse("e5653e8", 4)) == 0);

	mulm(parse("455", 4), parse("f7", 4), p, result);
	print(result);
	assert(cmp(result, parse("42e03", 4)) == 0);

	mulm(parse("bb6", 4), parse("ffca", 4), p, result);
	print(result);
	assert(cmp(result, parse("bb3879c", 4)) == 0);

	mulm(parse("529", 4), parse("4641eb63", 4), p, result);
	print(result);
	assert(cmp(result, parse("a27a4b0", 4)) == 0);

	mulm(parse("6", 4), parse("54266", 4), p, result);
	print(result);
	assert(cmp(result, parse("1f8e64", 4)) == 0);

	mulm(parse("47fcd646", 4), parse("acb0", 4), p, result);
	print(result);
	assert(cmp(result, parse("5dcab93e", 4)) == 0);

	mulm(parse("2", 4), parse("37cb643", 4), p, result);
	print(result);
	assert(cmp(result, parse("6f96c86", 4)) == 0);

	mulm(parse("abd", 4), parse("e45b", 4), p, result);
	print(result);
	assert(cmp(result, parse("994252f", 4)) == 0);

	mulm(parse("3a2edfc2", 4), parse("df17003", 4), p, result);
	print(result);
	assert(cmp(result, parse("366a012b", 4)) == 0);

	mulm(parse("d473e", 4), parse("9ade9ae", 4), p, result);
	print(result);
	assert(cmp(result, parse("71c4db30", 4)) == 0);

	mulm(parse("a1030f", 4), parse("2b", 4), p, result);
	print(result);
	assert(cmp(result, parse("1b0b8385", 4)) == 0);

	mulm(parse("2365107", 4), parse("155559fe", 4), p, result);
	print(result);
	assert(cmp(result, parse("ec136dd", 4)) == 0);

	mulm(parse("1d2a4bd", 4), parse("b6a256", 4), p, result);
	print(result);
	assert(cmp(result, parse("7638b50", 4)) == 0);

	mulm(parse("72573fe", 4), parse("36312006", 4), p, result);
	print(result);
	assert(cmp(result, parse("24050303", 4)) == 0);

	mulm(parse("555d7", 4), parse("6", 4), p, result);
	print(result);
	assert(cmp(result, parse("20030a", 4)) == 0);

	mulm(parse("9ff8b4c", 4), parse("631f8b6f", 4), p, result);
	print(result);
	assert(cmp(result, parse("6061c678", 4)) == 0);

	mulm(parse("6a6c", 4), parse("b978", 4), p, result);
	print(result);
	assert(cmp(result, parse("4d19eea0", 4)) == 0);

	mulm(parse("8", 4), parse("721b", 4), p, result);
	print(result);
	assert(cmp(result, parse("390d8", 4)) == 0);

	mulm(parse("2f316f60", 4), parse("1a", 4), p, result);
	print(result);
	assert(cmp(result, parse("4b054fc9", 4)) == 0);

	mulm(parse("736329", 4), parse("69e8a", 4), p, result);
	print(result);
	assert(cmp(result, parse("485cc811", 4)) == 0);

	mulm(parse("4211d134", 4), parse("73034", 4), p, result);
	print(result);
	assert(cmp(result, parse("7b47f46a", 4)) == 0);

	mulm(parse("38", 4), parse("109f35", 4), p, result);
	print(result);
	assert(cmp(result, parse("3a2d398", 4)) == 0);

	mulm(parse("c060c0", 4), parse("9", 4), p, result);
	print(result);
	assert(cmp(result, parse("6c366c0", 4)) == 0);

	mulm(parse("3d7cc", 4), parse("47", 4), p, result);
	print(result);
	assert(cmp(result, parse("110d994", 4)) == 0);

	divm(parse("1cb9", 4), parse("a", 4), p, result);
	print(result);
	assert(cmp(result, parse("ccccfac", 4)) == 0);

	divm(parse("b82add", 4), parse("bc", 4), p, result);
	print(result);
	assert(cmp(result, parse("31b4b96b", 4)) == 0);

	divm(parse("c568a", 4), parse("52c8", 4), p, result);
	print(result);
	assert(cmp(result, parse("404720b7", 4)) == 0);

	divm(parse("f7b", 4), parse("9", 4), p, result);
	print(result);
	assert(cmp(result, parse("5555570d", 4)) == 0);

	divm(parse("3929e4", 4), parse("65ce1ba", 4), p, result);
	print(result);
	assert(cmp(result, parse("76dc6295", 4)) == 0);

	divm(parse("55", 4), parse("b977", 4), p, result);
	print(result);
	assert(cmp(result, parse("37f59ac0", 4)) == 0);

	divm(parse("c52", 4), parse("cc1164", 4), p, result);
	print(result);
	assert(cmp(result, parse("2f7ed69e", 4)) == 0);

	divm(parse("40a90c", 4), parse("36004622", 4), p, result);
	print(result);
	assert(cmp(result, parse("677c0f0f", 4)) == 0);

	divm(parse("f1", 4), parse("4c2f87", 4), p, result);
	print(result);
	assert(cmp(result, parse("a634b17", 4)) == 0);

	divm(parse("c12", 4), parse("8f5a", 4), p, result);
	print(result);
	assert(cmp(result, parse("4b01214d", 4)) == 0);

	divm(parse("a3c47", 4), parse("da1d", 4), p, result);
	print(result);
	assert(cmp(result, parse("589771c5", 4)) == 0);

	divm(parse("d53e7e", 4), parse("b1", 4), p, result);
	print(result);
	assert(cmp(result, parse("4626cf2d", 4)) == 0);

	divm(parse("bf", 4), parse("1816", 4), p, result);
	print(result);
	assert(cmp(result, parse("2e05d001", 4)) == 0);

	divm(parse("32b", 4), parse("267d5", 4), p, result);
	print(result);
	assert(cmp(result, parse("3de41cce", 4)) == 0);

	divm(parse("7a5", 4), parse("8f", 4), p, result);
	print(result);
	assert(cmp(result, parse("4faa11f4", 4)) == 0);

	divm(parse("df", 4), parse("b68", 4), p, result);
	print(result);
	assert(cmp(result, parse("35f62e4a", 4)) == 0);

	divm(parse("44012", 4), parse("31e", 4), p, result);
	print(result);
	assert(cmp(result, parse("5dfeb8dc", 4)) == 0);

	divm(parse("f07ff", 4), parse("6fa", 4), p, result);
	print(result);
	assert(cmp(result, parse("47060750", 4)) == 0);

	divm(parse("17e7cc", 4), parse("2", 4), p, result);
	print(result);
	assert(cmp(result, parse("bf3e6", 4)) == 0);

	divm(parse("724a690", 4), parse("4547c03", 4), p, result);
	print(result);
	assert(cmp(result, parse("5448f86b", 4)) == 0);

	divm(parse("dd7", 4), parse("92e1", 4), p, result);
	print(result);
	assert(cmp(result, parse("3245d007", 4)) == 0);

	divm(parse("2f0afb", 4), parse("7", 4), p, result);
	print(result);
	assert(cmp(result, parse("6b86d", 4)) == 0);

	divm(parse("6d384c", 4), parse("de8f67", 4), p, result);
	print(result);
	assert(cmp(result, parse("37e35e91", 4)) == 0);

	divm(parse("78827f01", 4), parse("9fa6", 4), p, result);
	print(result);
	assert(cmp(result, parse("4600ee23", 4)) == 0);

	divm(parse("20f", 4), parse("d861", 4), p, result);
	print(result);
	assert(cmp(result, parse("62a57a6d", 4)) == 0);

	divm(parse("2bee1", 4), parse("333c", 4), p, result);
	print(result);
	assert(cmp(result, parse("2d2cbc5d", 4)) == 0);

	divm(parse("e6", 4), parse("af77", 4), p, result);
	print(result);
	assert(cmp(result, parse("7f583793", 4)) == 0);

	divm(parse("c11", 4), parse("c7", 4), p, result);
	print(result);
	assert(cmp(result, parse("5a0cdd53", 4)) == 0);

	divm(parse("b729", 4), parse("9a0", 4), p, result);
	print(result);
	assert(cmp(result, parse("643531f1", 4)) == 0);

	divm(parse("d09c0", 4), parse("fe", 4), p, result);
	print(result);
	assert(cmp(result, parse("48912f68", 4)) == 0);

	divm(parse("145c", 4), parse("b", 4), p, result);
	print(result);
	assert(cmp(result, parse("1745d34e", 4)) == 0);

	divm(parse("4d16", 4), parse("afab87e", 4), p, result);
	print(result);
	assert(cmp(result, parse("1584c76c", 4)) == 0);

	divm(parse("8e6cc9", 4), parse("3f8", 4), p, result);
	print(result);
	assert(cmp(result, parse("49b38ab0", 4)) == 0);

	divm(parse("65", 4), parse("5f", 4), p, result);
	print(result);
	assert(cmp(result, parse("7bf53897", 4)) == 0);

	divm(parse("3d5ee", 4), parse("e81e", 4), p, result);
	print(result);
	assert(cmp(result, parse("7e8e885", 4)) == 0);

	divm(parse("b0", 4), parse("2451", 4), p, result);
	print(result);
	assert(cmp(result, parse("7585cbd8", 4)) == 0);

	divm(parse("b5390d", 4), parse("2bd8b", 4), p, result);
	print(result);
	assert(cmp(result, parse("14f5744a", 4)) == 0);

	divm(parse("c74", 4), parse("7b", 4), p, result);
	print(result);
	assert(cmp(result, parse("6e4f16fe", 4)) == 0);

	divm(parse("466ca", 4), parse("1", 4), p, result);
	print(result);
	assert(cmp(result, parse("466ca", 4)) == 0);

	divm(parse("a9", 4), parse("18f", 4), p, result);
	print(result);
	assert(cmp(result, parse("66a819b", 4)) == 0);

	divm(parse("99", 4), parse("b0f9e", 4), p, result);
	print(result);
	assert(cmp(result, parse("5df0f219", 4)) == 0);

	divm(parse("b22fbe", 4), parse("dea", 4), p, result);
	print(result);
	assert(cmp(result, parse("388fca1c", 4)) == 0);

	divm(parse("8668f7", 4), parse("c", 4), p, result);
	print(result);
	assert(cmp(result, parse("4ab5de14", 4)) == 0);

	divm(parse("69", 4), parse("72", 4), p, result);
	print(result);
	assert(cmp(result, parse("250d7944", 4)) == 0);

	divm(parse("d3f2", 4), parse("316c3", 4), p, result);
	print(result);
	assert(cmp(result, parse("35a5f52c", 4)) == 0);

	divm(parse("d34d7", 4), parse("6106e32f", 4), p, result);
	print(result);
	assert(cmp(result, parse("225e03e2", 4)) == 0);

	divm(parse("a078", 4), parse("d5", 4), p, result);
	print(result);
	assert(cmp(result, parse("237495c9", 4)) == 0);

	divm(parse("5cfc", 4), parse("2abeac82", 4), p, result);
	print(result);
	assert(cmp(result, parse("dc4992c", 4)) == 0);

	divm(parse("34699", 4), parse("8c", 4), p, result);
	print(result);
	assert(cmp(result, parse("21d4233f", 4)) == 0);

	divm(parse("8a0f1e8", 4), parse("4", 4), p, result);
	print(result);
	assert(cmp(result, parse("2283c7a", 4)) == 0);

	divm(parse("45", 4), parse("f74af7e", 4), p, result);
	print(result);
	assert(cmp(result, parse("4eaecaa1", 4)) == 0);

	divm(parse("37", 4), parse("379fe5", 4), p, result);
	print(result);
	assert(cmp(result, parse("4157e87d", 4)) == 0);

	divm(parse("7f9a", 4), parse("54", 4), p, result);
	print(result);
	assert(cmp(result, parse("f3cf554", 4)) == 0);

	divm(parse("3da435e0", 4), parse("d056d", 4), p, result);
	print(result);
	assert(cmp(result, parse("1aa9b2af", 4)) == 0);

	divm(parse("a8d1eb", 4), parse("4a", 4), p, result);
	print(result);
	assert(cmp(result, parse("391709c1", 4)) == 0);

	divm(parse("8", 4), parse("a", 4), p, result);
	print(result);
	assert(cmp(result, parse("4ccccccd", 4)) == 0);

	divm(parse("fd080", 4), parse("483e", 4), p, result);
	print(result);
	assert(cmp(result, parse("695a9cdb", 4)) == 0);

	divm(parse("7a1b6109", 4), parse("6d22", 4), p, result);
	print(result);
	assert(cmp(result, parse("2171fd93", 4)) == 0);

	divm(parse("d2cd9", 4), parse("115b5", 4), p, result);
	print(result);
	assert(cmp(result, parse("c459cf5", 4)) == 0);

	divm(parse("75436", 4), parse("22d", 4), p, result);
	print(result);
	assert(cmp(result, parse("6d9da85d", 4)) == 0);

	divm(parse("b82bbcf", 4), parse("ac09ed", 4), p, result);
	print(result);
	assert(cmp(result, parse("282daa09", 4)) == 0);

	divm(parse("9d68398", 4), parse("ea4c", 4), p, result);
	print(result);
	assert(cmp(result, parse("396e7baa", 4)) == 0);

	divm(parse("8afd1e", 4), parse("bb67a", 4), p, result);
	print(result);
	assert(cmp(result, parse("6f46df1a", 4)) == 0);

	divm(parse("7b", 4), parse("4969b222", 4), p, result);
	print(result);
	assert(cmp(result, parse("46aae47", 4)) == 0);

	divm(parse("7ee48d", 4), parse("5", 4), p, result);
	print(result);
	assert(cmp(result, parse("1960e9", 4)) == 0);

	divm(parse("bf734", 4), parse("ae", 4), p, result);
	print(result);
	assert(cmp(result, parse("3ad9d0de", 4)) == 0);

	divm(parse("582455f", 4), parse("cf37a42", 4), p, result);
	print(result);
	assert(cmp(result, parse("70a6017e", 4)) == 0);

	divm(parse("46e0", 4), parse("303", 4), p, result);
	print(result);
	assert(cmp(result, parse("877888f", 4)) == 0);

	divm(parse("445429", 4), parse("4", 4), p, result);
	print(result);
	assert(cmp(result, parse("2011150a", 4)) == 0);

	divm(parse("269", 4), parse("1011432", 4), p, result);
	print(result);
	assert(cmp(result, parse("72039a58", 4)) == 0);

	divm(parse("839e3", 4), parse("c4b", 4), p, result);
	print(result);
	assert(cmp(result, parse("321c302", 4)) == 0);

	divm(parse("21ed", 4), parse("86fe", 4), p, result);
	print(result);
	assert(cmp(result, parse("4ce5a496", 4)) == 0);

	divm(parse("8e9", 4), parse("908c510", 4), p, result);
	print(result);
	assert(cmp(result, parse("682fa6ad", 4)) == 0);

	divm(parse("4", 4), parse("7", 4), p, result);
	print(result);
	assert(cmp(result, parse("36db6db7", 4)) == 0);

	divm(parse("54ac7", 4), parse("17658", 4), p, result);
	print(result);
	assert(cmp(result, parse("65ea6a65", 4)) == 0);

	divm(parse("fc3f1", 4), parse("24b06461", 4), p, result);
	print(result);
	assert(cmp(result, parse("179e6e1c", 4)) == 0);

	divm(parse("c7a", 4), parse("2ef", 4), p, result);
	print(result);
	assert(cmp(result, parse("3f100578", 4)) == 0);

	divm(parse("78640917", 4), parse("41788", 4), p, result);
	print(result);
	assert(cmp(result, parse("422abea3", 4)) == 0);

	divm(parse("6340", 4), parse("1fe", 4), p, result);
	print(result);
	assert(cmp(result, parse("51d1d203", 4)) == 0);

	divm(parse("cb3f7e2", 4), parse("4de02702", 4), p, result);
	print(result);
	assert(cmp(result, parse("71154b66", 4)) == 0);

	divm(parse("98321d9", 4), parse("a", 4), p, result);
	print(result);
	assert(cmp(result, parse("40f38362", 4)) == 0);

	divm(parse("797", 4), parse("ac2a213", 4), p, result);
	print(result);
	assert(cmp(result, parse("4352ada8", 4)) == 0);

	divm(parse("605306d", 4), parse("d8", 4), p, result);
	print(result);
	assert(cmp(result, parse("455c77ed", 4)) == 0);

	divm(parse("816c75", 4), parse("eabf", 4), p, result);
	print(result);
	assert(cmp(result, parse("6a272af9", 4)) == 0);

	divm(parse("96", 4), parse("bd9f", 4), p, result);
	print(result);
	assert(cmp(result, parse("509db437", 4)) == 0);

	divm(parse("a603c9", 4), parse("a", 4), p, result);
	print(result);
	assert(cmp(result, parse("401099fa", 4)) == 0);

	divm(parse("951", 4), parse("7", 4), p, result);
	print(result);
	assert(cmp(result, parse("24924a79", 4)) == 0);

	divm(parse("3dfb", 4), parse("f", 4), p, result);
	print(result);
	assert(cmp(result, parse("4cccd0ee", 4)) == 0);

	divm(parse("ee4f50d", 4), parse("dc92", 4), p, result);
	print(result);
	assert(cmp(result, parse("71f06183", 4)) == 0);

	divm(parse("7cd", 4), parse("6ed9add8", 4), p, result);
	print(result);
	assert(cmp(result, parse("4ee5dfe3", 4)) == 0);

	divm(parse("27", 4), parse("d390", 4), p, result);
	print(result);
	assert(cmp(result, parse("444ef494", 4)) == 0);

	divm(parse("8655f4", 4), parse("6a4d1", 4), p, result);
	print(result);
	assert(cmp(result, parse("7f2b8c0a", 4)) == 0);

	divm(parse("812715b", 4), parse("7511e", 4), p, result);
	print(result);
	assert(cmp(result, parse("6b2b2fd6", 4)) == 0);

	divm(parse("5ebf", 4), parse("6c24af59", 4), p, result);
	print(result);
	assert(cmp(result, parse("5199d9cc", 4)) == 0);

	divm(parse("21f2067e", 4), parse("52fdf", 4), p, result);
	print(result);
	assert(cmp(result, parse("7cc6c9f0", 4)) == 0);

	divm(parse("11", 4), parse("b", 4), p, result);
	print(result);
	assert(cmp(result, parse("3a2e8ba4", 4)) == 0);

	divm(parse("d9731", 4), parse("3947ec", 4), p, result);
	print(result);
	assert(cmp(result, parse("79a99e89", 4)) == 0);

	divm(parse("9263c4", 4), parse("7", 4), p, result);
	print(result);
	assert(cmp(result, parse("5b82a089", 4)) == 0);

	divm(parse("2844", 4), parse("b8c454", 4), p, result);
	print(result);
	assert(cmp(result, parse("79574fc5", 4)) == 0);

	divm(parse("fe2d0ce", 4), parse("4037", 4), p, result);
	print(result);
	assert(cmp(result, parse("1906bdc0", 4)) == 0);

}
