/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, you can obtain one at
 * https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2025 Lander Gallastegi (LNDF)
 */

#pragma once

#define PSSCLOUD_RESPONSE_CONFIG_MAIN_DATA "{\"registration\":{\"enabled\":true}}"

#define PSSCLOUD_RESPONSE_AUTH_PART1 "{\"token\":\"eyJhbGciOiJSUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJkdW1teS1pc3N1ZXIubmV0Iiwic3ViIjoiZHVtbXlTdWJqZWN0IiwiZXhwIjoxNzM4MDkyNDY3LCJuYmYiOjE3MzgwODg4NjcsImlhdCI6MTczODA4ODg2NywianRpIjoiZHVtbXlKVEkiLCJucyI6ImR1bW15TmFtZXNwYWNlIiwicm9sIjpbImR1bW15Um9sZSJdLCJkbiI6ImR1bW15RE4ifQopjPjc84hKCpjdy34CD2tc.hZXlisfZ6dRjmNdUn0sj5Q7i42CZFoF_9GMIVinsdVEaZLxPH1ohNxN-vdZg18ovcw7FlecY6XlXBzpU382CIjpKss6Drm7mYRfYl9p2M1Lv-Bh0iZcKcj_XZwOtJZZbQM2Fj-xmXC7wFoGiWIWlOEaYB-TTjteZ0uGKBBV6PaRpykW3kcBrfdiB92WrwlbazVRdg62_BSfN_wGQSAxZ9tdQlRqVjI0V4eTo1Gl7ZdVZy9l0xciDxhpYg0kaRs-wYZ6wZMODhtdhNYX12MCdIuVDhEU2NqAU7GX8djKLSjMeCM09vfBwVjcgy87Zrj8LX1zJQS9fJZkW-M9LstIDzA\",\"account\":{\"name\":\"ns/"
#define PSSCLOUD_RESPONSE_AUTH_PART2 "/accounts/2mcc1pdmkRPXeP6jpAa48tcNFWz\",\"id\":\"2mcc1pdmkRPXeP6jpAa48tcNFWz\",\"origin\":{\"platform\":\"STEAM\",\"id\":\"46231443256534370\",\"attributes\":{}},\"displayName\":\"steamuser\",\"createTime\":\"1970-01-01T00:00:00Z\",\"updateTime\":\"1970-01-01T00:00:00Z\"}}"

#define PSSCLOUD_RESPONSE_REGISTRATION_PRODUCT_PART1 "{\"clientId\":\"143561c1-4b3d-4c13-8b3a-9e419d96b9c4\",\"scope\":\"openid id_token:psn.basic_claims id_token:is_child psn:passiveLink.steam.s2s\",\"redirectUri\":\"orbis://games\",\"smcid\":\"pc:STEAM:"
#define PSSCLOUD_RESPONSE_REGISTRATION_PRODUCT_PART2 ":PPSA25000_00\"}"

#define PSSCLOUD_RESPONSE_REGISTERED_ACCOUNT_PART1 "{\"name\":\"ns/shared/accounts/23k19CI2nclpPj3np00dnCy2n1x\",\"id\":\"23k19CI2nclpPj3np00dnCy2n1x\",\"origin\":{\"platform\":\"PSN_NP\",\"id\":\""
#define PSSCLOUD_RESPONSE_REGISTERED_ACCOUNT_PART2 "\",\"attributes\":{\"is_child\":false,\"legal_country\":\"US\",\"locale\":\"en-US\",\"signin_id\":\"example@example.com\"}},\"displayName\":\"Player\",\"createTime\":\"1970-00-00T00:00:00Z\",\"updateTime\":\"1970-00-00T00:00:00Z\"}"

#define PSSCLOUD_RESPONSE_NEW_REGISTRATION_URL_PART1 "{\"url\":\"https://pss-cloud.net/gs/accounts/v1/ns/"
#define PSSCLOUD_RESPONSE_NEW_REGISTRATION_URL_PART2 ":register?linkToken=jcqc34rNp41PAx1lN34mcyx1mDv\"}"

#define PSSCLOUD_RESPONSE_LINK_PART1 "{\"account\":{\"name\":\"ns/shared/accounts/23k19CI2nclpPj3np00dnCy2n1x\",\"id\":\"23k19CI2nclpPj3np00dnCy2n1x\",\"origin\":{\"platform\":\"PSN_NP\",\"id\":\""
#define PSSCLOUD_RESPONSE_LINK_PART2 "\",\"attributes\":{\"is_child\":false,\"legal_country\":\"US\",\"locale\":\"en-US\",\"signin_id\":\"example@example.com\"}},\"displayName\":\"Player\",\"createTime\":\"1970-00-00T00:00:00.000000000Z\",\"updateTime\":\"1970-00-00T00:00:00.000000000Z\"}}"
