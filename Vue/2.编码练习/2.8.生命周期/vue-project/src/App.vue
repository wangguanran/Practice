<script lang="ts" setup>
import { onBeforeMount, onBeforeUnmount, onBeforeUpdate, onMounted, onUnmounted, onUpdated, ref } from 'vue';

let sum = ref(0);

function changeSum() {
    sum.value++;
}
console.log('App.vue setup');

onBeforeMount(() => {
    console.log('App.vue onBeforeMount');
});
onMounted(() => {
    console.log('App.vue onMounted');
});
onBeforeUpdate(() => {
    console.log('App.vue onBeforeUpdate');
});
onUpdated(() => {
    console.log('App.vue onUpdated');
});
onBeforeUnmount(() => {
    console.log('App.vue onBeforeUnmount');
});
onUnmounted(() => {
    console.log('App.vue onUnmounted');
});
</script>

<template>
    <div>
        <h2>当前求和为：{{ sum }}</h2>
        <button @click="changeSum">点我sum+1</button>
    </div>
</template>

<style scoped></style>
